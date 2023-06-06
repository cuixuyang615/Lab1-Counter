# Task1 result
## Original code

The original code waveform is shown as in Fig.1.
![The waveform of original code](./original_waveform.PNG "The waveform of original code")

The rst signal has been reseted when counter reaches 0x09, and this is because of:

` top->rst = (i<2) | (i==15);`

So rst will be set to 1 at 15th clock cycle, and so as in the first 2 clock cycle.

## Challenge code 

modify the testbench code of en and rst signal to:

'
//  challenge code:
    top->rst = (i<2);

    if(top->count == 0x9)
    {
        if(j<2)
        {
            top->en = 0;
            j++;
        }
        else
        {
            top->en = 1;
        }
    }
    else
    {
        top->en = 1;
        j=0;
    }
'

This make rst only set to 1 at first 2 cycle and make en set to 0 for 2 cycles when count reaches 0x9.
Because at the next rising edge the 

'count <= count + {{(WIDTH-1){1'b0}}, en};'

statement will be 
