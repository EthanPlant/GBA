typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int          uint32;

#define REG_DISPLAYCONTROL	*((volatile uint32*)(0x04000000))
#define VIDEOMODE_3     	               0x0003
#define BGMODE_2 			       0x0400

#define SCREENBUFFER                    ((volatile uint16*)0x06000000)
#define SCREEN_W                            240
#define SCREEN_H                            160

int main()
{
    REG_DISPLAYCONTROL = VIDEOMODE_3 | BGMODE_2;

	for (int i = 0; i < SCREEN_W * SCREEN_H; ++i)
	{
		SCREENBUFFER[i] = 0x001F;
	}

    while(1){}
    return 0;
}   