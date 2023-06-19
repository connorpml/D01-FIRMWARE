#include "asf.h"
#include "inverter.h"

#define SERIAL_BUFFER_LEN 16

// Peak voltage in millivolts
#define CONF_MAX_OUTPUT_VOLTAGE 169706 // 120VAC * sqrt(2) * 1000 mV/V

// Max value of setpoint received via USART. 
// This translates to CONF_MAX_OUTPUT_VOLTAGE on the output
#define CONF_SETPOINT_MAX_VALUE 1000 

int main (void)
{
	uint8_t buffer[SERIAL_BUFFER_LEN];
	int data_len = 0;
	uint8_t* onOffCommand = 0;
	uint8_t* syncLedCommand = 0;
	uint8_t* setpointCommand = 0;
	bool parseError = false;
	int setpoint = 0;
	bool commandOutputEnable = false;
	bool syncLedEnable = false;
	
	system_init();

	// Configure LED pins as outputs
	struct port_config config_port_pin;
	port_get_config_defaults(&config_port_pin);
	config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(PIN_PA23, &config_port_pin);
	port_pin_set_config(PIN_PA27, &config_port_pin);
	port_pin_set_output_level(PIN_PA27, true);
	port_pin_set_output_level(PIN_PA23, true);
	
	delay_init();
	inverter_init();
	serial_init();

	// Main infinite loop
	while (true) {
		// Inverter housekeeping needs to be done each cycle
		inverter_housekeeping();
		
		// Reset parseError
		parseError = false;
		
		int len = serial_readline(buffer, SERIAL_BUFFER_LEN);
		
		// If we didn't read anything, skip and try again
		if (len == -1)
			continue;
		
		// Search through the line and find the parameters. Set the parameter characters to
		//   null so that we can treat each input as a NTCS and use functions like atoi()
		//   to parse the information. If we don't receive each character, something is wrong.
		bool foundS = false, foundV = false, foundL = false;
		
		for(int i = 0; i < len; i++) {
			if (buffer[i] == 'S') {
				onOffCommand = buffer+i+1;
				buffer[i] = 0;
				foundS = true;
			} else if (buffer[i] == 'V') {
				setpointCommand = buffer+i+1;
				buffer[i] = 0;
				foundV = true;
			} else if (buffer[i] == 'L') {
				syncLedCommand = buffer+i+1;
				buffer[i] = 0;
				foundL = true;
			}
				
			if (!foundS && !foundV && !foundL) {
				parseError = true;
			}
		}
		
		// Check the on/off command parameter
		if (!parseError && foundS) {
			switch(*onOffCommand) {
				case '1':
					commandOutputEnable = true;
					break;
				case '0':
					commandOutputEnable = false;
					break;
				default:
					parseError = true;
			}
		}
		
		// Check the syncLed command parameter
		if (!parseError && foundL) {
			switch(*syncLedCommand) {
				case '1':
					syncLedEnable = true;
					break;
				case '0':
					syncLedEnable = false;
					break;
				default:
					parseError = true;
			}
		}
		
		// Check the setpoint parameter
		if (!parseError && foundV) {
			setpoint = atoi((char*)setpointCommand);
			if (setpoint < 0 || setpoint > CONF_SETPOINT_MAX_VALUE)
				parseError = true;
		}
		
		if (!parseError && foundL) {
			port_pin_set_output_level(PIN_PA23, !syncLedEnable);
		}
		
		
		// Effect the changes
		if (!parseError && commandOutputEnable) {
			inverter_set_channels(0, (setpoint * CONF_MAX_OUTPUT_VOLTAGE) / CONF_SETPOINT_MAX_VALUE);
			data_len = sprintf(buffer, "S%iV%iL%i", commandOutputEnable, setpoint, syncLedEnable);
			serial_writeline(buffer, data_len);
		} else {
			inverter_set_channels(0, 0);
			data_len = sprintf(buffer, "S0V0L%i", syncLedEnable);
			serial_writeline(buffer, data_len);	
		}
	}
}
