#include <nds.h>
#include <stdio.h>
#include <maxmod9.h>

#include "nds/ndstypes.h"
#include "nds/arm9/video.h"
#include "nds/memory.h"
#include "nds/system.h"
#include "drunkenlogo.h"
#include "font.h"



#define sample_rate  8000

u16* sound_buffer = 0;
u16* mic_buffer = 0;
u32 data_length = 0;
u32 sound_buffer_size = sample_rate * 2 * 5;
u32 mic_buffer_size = sample_rate * 2 / 30;

int microphoneWhile = 1;
bool isinmenu = false;
bool istestingbuttons = false;
bool istestingtscreen = false;
bool istestingmicrophone = false;
int todoSelection = 0;
touchPosition touchXY;
PrintConsole top, bottom;

void micHandler(void* data, int length)
{
	
	if (!sound_buffer || data_length > sound_buffer_size) return;


	DC_InvalidateRange(data, length);

	dmaCopy(data, ((u8*)sound_buffer) + data_length, length);

	data_length += length;

	iprintf(".");

}

void record(void)
{
	
	data_length = 0;
	soundMicRecord(mic_buffer, mic_buffer_size, MicFormat_12Bit, sample_rate, micHandler);
}

void play(void)
{
	soundMicOff();
	soundEnable();
	iprintf("data length: %li\n", data_length);
	soundPlaySample(sound_buffer, SoundFormat_16Bit, data_length, sample_rate, 127, 64, false, 0);
}

void mainmenu(void) {
	microphoneWhile = 0;
	isinmenu = true;
	todoSelection = 0;
	consoleInit(&top, 0, BgType_Text4bpp, BgSize_T_256x256, 2, 0, true, true);
	consoleInit(&bottom, 0, BgType_Text4bpp, BgSize_T_256x256, 2, 0, false, true);
	istestingtscreen = false;
	istestingbuttons = false;
	istestingmicrophone = false;
	

	consoleSelect(&top);
	iprintf("What do you want to test?\n\n");
	iprintf("Buttons     <-\n");
	iprintf("TouchScreen\n");
	if (isDSiMode()) {}else{
		iprintf("Microphone\n");
	}


}

int main(void) {
	

	soundEnable();
	

	videoSetMode(MODE_3_2D);
	videoSetModeSub(MODE_3_2D);
	vramSetBankA(VRAM_A_MAIN_BG);
	vramSetBankC(VRAM_C_SUB_BG);
	bgInit(3, BgType_Bmp16, BgSize_B16_256x256, 1, 0);
	bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 1, 0);
	decompress(drunkenlogoBitmap, BG_GFX, LZ77Vram);
	consoleDemoInit();
	const int tile_base = 0;
const int map_base = 2;
	consoleInit(&top,0, BgType_Text4bpp, BgSize_T_256x256, map_base, tile_base, true, true);
	consoleInit(&bottom, 0, BgType_Text4bpp, BgSize_T_256x256, 2, 0, false, true);

	consoleSelect(&top);

	/*font.gfx = (u16*)fontTiles;
	font.pal = (u16*)fontPal;
	font.numChars = 95;
	font.numColors =  fontPalLen / 2;
	font.bpp = 4;
	font.asciiOffset = 32;
	font.convertSingleColor = false;*/
	
	ConsoleFont font;
	consoleSetFont(&top, &font);
	iprintf("GreenTester DS v1.0\n");
	iprintf("GreenSoupDev - 2023\n\n");
	iprintf("Welcome, hold select and then\npress Start to continue\n\n");
	iprintf("To exit, hold Select\nand then press the Down button\n");
	sound_buffer = (u16*)malloc(sound_buffer_size);
	mic_buffer = (u16*)malloc(mic_buffer_size);
	while(1) {
	
		touchRead(&touchXY);
		swiWaitForVBlank();
		scanKeys();		
		if (KEY_SELECT & keysHeld()) { if (keysDown() & KEY_DOWN){ exit(0); }}
		
			if (KEY_SELECT & keysHeld()) {
				if (keysDown() & KEY_START) {
					mainmenu();
				}
			}
		
		if (isinmenu == true)
		{
			if (todoSelection < 0){todoSelection = 0;}
			if (isDSiMode()) {
				if (todoSelection > 1){todoSelection = 1;}
			}else{				
				if (todoSelection > 2){todoSelection = 2;}
			}
			
			if (keysDown() & KEY_UP){
				consoleSelect(&top);
				consoleInit(&top, 0, BgType_Text4bpp, BgSize_T_256x256, 2, 0, true, true);
				iprintf("What do you want to test?\n\n");
				if (todoSelection > 0){todoSelection -= 1;}				
				if (todoSelection == 0) {
					consoleSelect(&top);
					iprintf("Buttons     <-\n");
					iprintf("TouchScreen\n");
					if (isDSiMode()) {}else{
						iprintf("Microphone\n");}
					}
				if (todoSelection == 1){
					consoleSelect(&top);
					iprintf("Buttons\n");
					iprintf("TouchScreen <-\n");
					if (isDSiMode()) {}else{
						iprintf("Microphone\n");}
					}
				if (todoSelection == 2) {
					consoleSelect(&top);
					iprintf("Buttons aaaa\n");
					iprintf("TouchScreen\n");
					if (isDSiMode()) {}else{
						iprintf("Microphone  <-\n");}
					}

					
	
	
					
				
			}
			if (keysDown() & KEY_DOWN){
				consoleSelect(&top);
				consoleInit(&top, 0, BgType_Text4bpp, BgSize_T_256x256, 2, 0, true, true);
				iprintf("What do you want to test?\n\n");
				if (isDSiMode()) {
				    if (todoSelection < 1){todoSelection += 1;}
			    }else{				
				    if (todoSelection < 2){todoSelection += 1;}
			    }
				
				if (todoSelection == 0) {
					consoleSelect(&top);
					iprintf("Buttons     <-\n");
					iprintf("TouchScreen\n");
					if (isDSiMode()) {}else{
						iprintf("Microphone\n");
					}
				}
				if (todoSelection == 1){
					consoleSelect(&top);
					iprintf("Buttons\n");
					iprintf("TouchScreen <-\n");
					if (isDSiMode()) {}else{
						iprintf("Microphone\n");
					}
				}
				if (todoSelection == 2) {
					consoleSelect(&top);
					iprintf("Buttons\n");
					iprintf("TouchScreen\n");
					
					if (isDSiMode()) {}else{
						iprintf("Microphone  <-\n");
					}
					
				}
			}
			if (todoSelection == 0)
			{
				if (keysDown() & KEY_A || keysDown() & KEY_B || keysDown() & KEY_Y || keysDown() & KEY_X)
				{
					istestingbuttons = true;
					istestingtscreen = false;					
					istestingmicrophone = false;
					consoleInit(&top, 0, BgType_Text4bpp, BgSize_T_256x256, 2, 0, true, true);
					consoleInit(&bottom, 0, BgType_Text4bpp, BgSize_T_256x256, 2, 0, false, true);
					consoleSelect(&top);
					iprintf("Press any button to test it.\n\n");
					iprintf("Hold Select and then press Startto go back.\n\n");
				}
			}
			if (todoSelection == 1)
			{
				if (keysDown() & KEY_A || keysDown() & KEY_B || keysDown() & KEY_Y || keysDown() & KEY_X)
				{
					istestingbuttons = false;
					istestingtscreen = true;					
					istestingmicrophone = false;
					consoleInit(&top, 0, BgType_Text4bpp, BgSize_T_256x256, 2, 0, true, true);
					consoleInit(&bottom, 0, BgType_Text4bpp, BgSize_T_256x256, 2, 0, false, true);
					consoleSelect(&top);
					iprintf("Touch the screen to test it.\n\n");
					iprintf("Hold Select and then press Startto go back.\n\n");
				}
			}
			if (todoSelection == 2)
			{
				if (keysDown() & KEY_A || keysDown() & KEY_B || keysDown() & KEY_Y || keysDown() & KEY_X)
				{
					microphoneWhile = 0;
					istestingbuttons = false;
					istestingtscreen = false;
					istestingmicrophone = true;
					consoleInit(&top, 0, BgType_Text4bpp, BgSize_T_256x256, 2, 0, true, true);
					consoleInit(&bottom, 0, BgType_Text4bpp, BgSize_T_256x256, 2, 0, false, true);
					consoleSelect(&top);
					iprintf("Say something to test the microphone.\n\n");
					iprintf("Hold Select and then press Startto go back.\n\n");
				}
			}
		}	
		

		if (istestingtscreen == true)
		{	
			
			
			isinmenu = false;
			
			consoleSelect(&bottom);
			iprintf("\x1b[16;0HTouch x = %04X, %04X\n", touchXY.rawx, touchXY.px);
			iprintf("Touch y = %04X, %04X\n", touchXY.rawy, touchXY.py);

			if (KEY_SELECT & keysHeld()) {
				if (keysDown() & KEY_START) {
					mainmenu();
				}
			}

		}
		if (istestingbuttons == true)
		{
			isinmenu = false;
			consoleSelect(&bottom);
			
			if (keysDown() & KEY_A)
			{
				iprintf("Button 'A' pressed.\n");
			}
			if (keysDown() & KEY_B)
			{
				iprintf("Button 'B' pressed.\n");
			}
			if (keysDown() & KEY_Y)
			{
				iprintf("Button 'Y' pressed.\n");
			}
			if (keysDown() & KEY_X)
			{
				iprintf("Button 'X' pressed.\n");
			}
			if (keysDown() & KEY_START)
			{
				iprintf("Button 'Start' pressed.\n");
			}
			if (keysDown() & KEY_SELECT)
			{
				iprintf("Button 'Select' pressed.\n");
			}
			if (keysDown() & KEY_L)
			{
				iprintf("Button 'L' pressed.\n");
			}
			if (keysDown() & KEY_R)
			{
				iprintf("Button 'R' pressed.\n");
			}

			if (keysDown() & KEY_UP)
			{
				iprintf("Button 'Up' pressed.\n");
			}
			if (keysDown() & KEY_DOWN)
			{
				iprintf("Button 'Down' pressed.\n");
			}
			if (keysDown() & KEY_LEFT)
			{
				iprintf("Button 'Left' pressed.\n");
			}
			if (keysDown() & KEY_RIGHT)
			{
				iprintf("Button 'Right' pressed.\n");
			}
			if (KEY_SELECT & keysHeld()) {
				if (keysDown() & KEY_START) {
					mainmenu();
				}
			}
			
		}
		if (istestingmicrophone == true)
		{
			isinmenu = false;
			consoleSelect(&bottom);
			


			
			int key;
			bool recording = false;

			sound_buffer = (u16*)malloc(sound_buffer_size);
			mic_buffer = (u16*)malloc(mic_buffer_size);

			consoleDemoInit();

			iprintf("Press A to record / play\n");
			microphoneWhile = 1;
				while (microphoneWhile)
				{
					if (istestingmicrophone == true)
					{


						scanKeys();
						key = keysDown();

						if (key & KEY_A)
						{
							recording ? play() : record();
							recording = !recording;
							iprintf("%s\n", recording ? "recording" : "playing");
						}

						if (KEY_SELECT & keysHeld()) {
							if (keysDown() & KEY_START) {
								mainmenu();
							}
						}

						swiWaitForVBlank();
					}

				}
			
			
			
			
		}
	}

	return 0;
}

