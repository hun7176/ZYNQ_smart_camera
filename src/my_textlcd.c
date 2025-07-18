#include "common.h"
int filter_num=0;
void print_textlcd(int sel){
    unsigned int RegVal[4] = {
        0x736d6172,  // 'smar'
        0x74206361,  // 't ca'
        0x6d657261,  // 'mera'
        0x20202020   // '    '
    };



	TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG0_OFFSET, RegVal[0]);
	TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG1_OFFSET, RegVal[1]);
	TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG2_OFFSET, RegVal[2]);
	TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG3_OFFSET, RegVal[3]);


switch (sel)
{
	case (0): //textlcd 첫줄 이건 고정시켜야함.
	{
		unsigned int RegVal[4] = {
				0x20202020,
				0x20202020,
				0x20202020,
				0x20202020

		};
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG0_OFFSET,RegVal[0]); // reg_a
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG1_OFFSET,RegVal[1]); // reg_b
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG2_OFFSET,RegVal[2]); // reg_c
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG3_OFFSET,RegVal[3]); // reg_d

		break;
	}
	case (1):
	{
		unsigned int RegVal[4] = {
			    0x63616d65,  // 'came'
			    0x7261206d,  // 'ra m'
			    0x6f646520,   // 'ode '
				0x20202020
		};

		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG4_OFFSET,RegVal[0]); // reg_a
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG5_OFFSET,RegVal[1]); // reg_b
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG6_OFFSET,RegVal[2]); // reg_c
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG7_OFFSET,RegVal[3]); // reg_d

		break;
	}
	case (2):
	{
		unsigned int RegVal[4] = {
		    0x63616d65,  // 'came'
		    0x72612063,  // 'ra c'
		    0x61707475,  // 'aptu'
		    0x72656420   // 'red '
		};

		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG4_OFFSET,RegVal[0]); // reg_a
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG5_OFFSET,RegVal[1]); // reg_b
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG6_OFFSET,RegVal[2]); // reg_c
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG7_OFFSET,RegVal[3]); // reg_d

		break;
	}
	case (3):
	{
	    unsigned int RegVal[4];

	    if(filter_num == 0){
	        unsigned int temp[4] = {
	            0x64656661,  // 'defa'
	            0x756c7420,  // 'ult '
	            0x20202020,  // padding
	            0x20202020   // padding
	        };
	        memcpy(RegVal, temp, sizeof(temp));
	    }
	    else if(filter_num == 1){
	        unsigned int temp[4] = {
	            0x65646765,  // 'edge'
	            0x20646574,  // ' det'
	            0x65637420,  // 'ect '
	            0x20202020   // padding
	        };
	        memcpy(RegVal, temp, sizeof(temp));
	    }
	    else if(filter_num == 2){
	        unsigned int temp[4] = {
	            0x626c7572,  // 'blur'
	            0x20202020,  // padding
	            0x20202020,  // padding
	            0x20202020   // padding
	        };
	        memcpy(RegVal, temp, sizeof(temp));
	    }
	    else if(filter_num == 3){
	        unsigned int temp[4] = {
	            0x656d626f,  // 'embo'
	            0x73732020,  // 'ss  '
	            0x20202020,  // padding
	            0x20202020   // padding
	        };
	        memcpy(RegVal, temp, sizeof(temp));
	    }
	    else if(filter_num == 4){
	        unsigned int temp[4] = {
	            0x73686172,  // 'shar'
	            0x70656e20,  // 'pen '
	            0x20202020,  // padding
	            0x20202020   // padding
	        };
	        memcpy(RegVal, temp, sizeof(temp));
	    }

	    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG4_OFFSET, RegVal[0]);
	    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG5_OFFSET, RegVal[1]);
	    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG6_OFFSET, RegVal[2]);
	    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG7_OFFSET, RegVal[3]);

	    filter_num++;
	    if(filter_num == 5) filter_num = 0;
	    break;
	}

	case (4):
	{
	    unsigned int RegVal[4] = {
	        0x6d792070,  // 'my p'
	        0x69637475,  // 'ictu'
	        0x72652020,  // 're  '
	        0x20202020   // padding
	    };

	    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG4_OFFSET, RegVal[0]); // reg_a
	    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG5_OFFSET, RegVal[1]); // reg_b
	    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG6_OFFSET, RegVal[2]); // reg_c
	    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG7_OFFSET, RegVal[3]); // reg_d

	    break;
	}
	case (5):
	{
	    unsigned int RegVal[4] = {
	        0x6C6F6164,  // 'load'
	        0x696E672E,  // 'ing.'
	        0x2E2E2E2E,  // '....'
	        0x20202020   // padding
	    };

	    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG4_OFFSET, RegVal[0]); // reg_a
	    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG5_OFFSET, RegVal[1]); // reg_b
	    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG6_OFFSET, RegVal[2]); // reg_c
	    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG7_OFFSET, RegVal[3]); // reg_d

	    break;
	}

	case (6):
	{
	    unsigned int RegVal[4] = {
	        0x4d41494e,  // 'MAIN'
	        0x20504147,  // ' PAG'
	        0x45202020,  // 'E   '
	        0x20202020   // padding
	    };

	    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG4_OFFSET, RegVal[0]);
	    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG5_OFFSET, RegVal[1]);
	    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG6_OFFSET, RegVal[2]);
	    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG7_OFFSET, RegVal[3]);

	    break;
	}

	case (7):
	{
	    unsigned int RegVal[4] = {
	        0x4D616465,  // 'Made'
	        0x20627920,  // ' by '
	        0x20202020,  // 공백
	        0x20202020   // 공백
	    };

	    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG4_OFFSET, RegVal[0]);
	    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG5_OFFSET, RegVal[1]);
	    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG6_OFFSET, RegVal[2]);
	    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG7_OFFSET, RegVal[3]);

	    break;
	}
	case (8): //갤러리
	{
	    unsigned int RegVal[4] = {
	        0x47414C4C,  // 'GALL'
	        0x45525920,  // 'ERY '
	        0x50414745,  // 'PAGE'
	        0x20202020   // padding
	    };
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG0_OFFSET,RegVal[0]); // reg_a
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG1_OFFSET,RegVal[1]); // reg_b
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG2_OFFSET,RegVal[2]); // reg_c
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG3_OFFSET,RegVal[3]); // reg_d

		break;
	}
}

}

void print_textlcd_line2(const char *str) {
    unsigned int RegVal[4] = {0, 0, 0, 0};

    for (int i = 0; i < 4; i++) {
        unsigned int word = 0;
        for (int j = 0; j < 4; j++) {
            char ch = str[i * 4 + j];
            if (ch == '\0') ch = ' ';  // null 이후는 공백 처리
            word = (word << 8) | ((unsigned int)ch);
        }
        RegVal[i] = word;
    }

    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG4_OFFSET, RegVal[0]);
    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG5_OFFSET, RegVal[1]);
    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG6_OFFSET, RegVal[2]);
    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG7_OFFSET, RegVal[3]);
}



void print_filter_textlcd(int sel){
	unsigned int RegVal[4] = {
	    0x3C46494C,  // '<FIL'
	    0x5445523E,  // 'TER>'
	    0x20202020,  // padding
	    0x20202020   // padding
	};

	TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG0_OFFSET,RegVal[0]); // reg_a
	TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG1_OFFSET,RegVal[1]); // reg_b
	TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG2_OFFSET,RegVal[2]); // reg_c
	TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG3_OFFSET,RegVal[3]); // reg_d

switch (sel)
{
	case (0): //textlcd 첫줄 이건 고정시켜야함.
	{
		unsigned int RegVal[4] = {
	            0x64656661,  // 'defa'
	            0x756c7420,  // 'ult '
	            0x20202020,  // padding
	            0x20202020   // padding

		};
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG4_OFFSET,RegVal[0]); // reg_a
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG5_OFFSET,RegVal[1]); // reg_b
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG6_OFFSET,RegVal[2]); // reg_c
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG7_OFFSET,RegVal[3]); // reg_d

		break;
	}
	case (1):
	{
		unsigned int RegVal[4] = {
	            0x65646765,  // 'edge'
	            0x20646574,  // ' det'
	            0x65637420,  // 'ect '
	            0x20202020   // padding
		};

		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG4_OFFSET,RegVal[0]); // reg_a
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG5_OFFSET,RegVal[1]); // reg_b
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG6_OFFSET,RegVal[2]); // reg_c
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG7_OFFSET,RegVal[3]); // reg_d

		break;
	}


	case (2): //textlcd 첫줄 이건 고정시켜야함.
	{
		unsigned int RegVal[4] = {
	            0x626c7572,  // 'blur'
	            0x20202020,  // padding
	            0x20202020,  // padding
	            0x20202020   // padding

		};
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG4_OFFSET,RegVal[0]); // reg_a
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG5_OFFSET,RegVal[1]); // reg_b
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG6_OFFSET,RegVal[2]); // reg_c
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG7_OFFSET,RegVal[3]); // reg_d

		break;
	}
	case (3): //textlcd 첫줄 이건 고정시켜야함.
	{
		unsigned int RegVal[4] = {
	            0x626c7572,  // 'blur'
	            0x20202020,  // padding
	            0x20202020,  // padding
				0x53494d44   // padding

		};
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG4_OFFSET,RegVal[0]); // reg_a
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG5_OFFSET,RegVal[1]); // reg_b
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG6_OFFSET,RegVal[2]); // reg_c
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG7_OFFSET,RegVal[3]); // reg_d

		break;
	}
	case (4):
	{
		unsigned int RegVal[4] = {
	            0x656d626f,  // 'embo'
	            0x73732020,  // 'ss  '
	            0x20202020,  // padding
	            0x20202020   // padding
		};

		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG4_OFFSET,RegVal[0]); // reg_a
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG5_OFFSET,RegVal[1]); // reg_b
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG6_OFFSET,RegVal[2]); // reg_c
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG7_OFFSET,RegVal[3]); // reg_d

		break;
	}

	case (5):
	{
	    unsigned int RegVal[4] = {
	        0x6e656761,  // 'nega'
	        0x74697665,  // 'tive'
	        0x20202020,  // padding
	        0x20202020   // padding
	    };

		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG4_OFFSET,RegVal[0]); // reg_a
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG5_OFFSET,RegVal[1]); // reg_b
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG6_OFFSET,RegVal[2]); // reg_c
		TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG7_OFFSET,RegVal[3]); // reg_d

		break;
	}
	case (6):
	{
	    unsigned int RegVal[4] = {
	        0x54696d65,  // 'Time'
	        0x64205368,  // 'd Sh'
	        0x6f742020,  // 'ot  '
	        0x20202020   // padding
	    };

	    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG4_OFFSET, RegVal[0]);
	    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG5_OFFSET, RegVal[1]);
	    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG6_OFFSET, RegVal[2]);
	    TEXTLCD_mWriteReg(XPAR_TEXTLCD_0_S00_AXI_BASEADDR, TEXTLCD_S00_AXI_SLV_REG7_OFFSET, RegVal[3]);

	    break;
	}


}

}
