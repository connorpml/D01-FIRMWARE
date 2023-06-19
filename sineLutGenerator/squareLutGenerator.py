from __future__ import division
import math

def generate_sine_table(length=256):    
    raw_table = []  
    for index, item in enumerate((i > 128) for i in xrange(length)):
        if divmod(index+1, 16)[-1]:
           raw_table.append(hex(int(item*0x400)))
        else:
           raw_table.append(hex(int(item*0x400)) + ',\n')
           
    output_table = []    
    for item in (raw_table[j:j+16] for j in xrange(0, len(raw_table), 16)):
        output_table.append(','.join(item))
    
    print(''.join(output_table))

if __name__ == '__main__':
    generate_sine_table()
