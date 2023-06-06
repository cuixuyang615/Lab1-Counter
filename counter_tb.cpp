#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char **argv, char **env)
{
    int i;
    int j=0;
    int clk;

    Verilated::commandArgs(argc, argv);

    Vcounter* top = new Vcounter;

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("counter.vcd");

    top->clk = 1;
    top->rst = 1;
    top->en  = 0;

    for(i=0; i<300; i++)
    {
        for(clk=0; clk<2; clk++)
        {
            tfp->dump(2*i+clk);
            top->clk = !top->clk;;
            top->eval();
        }

        // original code:
        top->rst = (i<2) | (i==15);
        top->en  = (i>4);

        // // challenge code:
        // top->rst = (i<2);

        // if(top->count == 0x9)
        // {
        //     if(j<2)
        //     {
        //         top->en = 0;
        //         j++;
        //     }
        //     else
        //     {
        //         top->en = 1;
        //     }
        // }
        // else
        // {
        //     top->en = 1;
        //     j=0;
        // }

        if(Verilated::gotFinish())
            exit(0);
    }

    tfp->close();
    exit(0);
}
