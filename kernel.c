void kernel_main();
void putc(char a);
void puts(char* string);

//
// kernel_main:
// Hoofdroutine voor onze kernel.
// Gebruikt voor alle onderdelen in te stellen
//
void kernel_main(){
	puts("Welkom bij CromaticOS, een besturingssysteem gemaakt door:\nSander\nSebastiaan");
}


unsigned int internecursorpointer = 0;
unsigned char* grafischgeheugenpointer = (unsigned char*) 0xb8000;
int curX = 0;
int curY = 0;
//
// putc
// plaats karakter op internecursorlocatie in het geheugen
// het geheugen voor video is 0xb8000 en werkt als volgd:
// byte1: karakter om te printen
// byte2: kleuren om in te printen, 0x?0 foreground 0x0? background
void putc(char a){
	if(a=='\n'){
		curX = 0;
		curY++;
	}else{
		internecursorpointer = (curX*2)+(curY*160);
		grafischgeheugenpointer[internecursorpointer++] = a; // karakter printen
		grafischgeheugenpointer[internecursorpointer++] = 0x07; // grafische eigenschappen printen
		curX++;
		if(curX==80){
			curX = 0;
			curY++;
		}
	}
}

//
// puts
// gaat de hele string door en laat het karakter op het scherm komen totdat hij op het 0x00 karakter komt, en dus het einde van de string is
void puts(char* string){
	int pointer = 0;
	char deze = 0x00;
	while((deze = string[pointer++])!=0x00){
		putc(deze);
	}
} 
