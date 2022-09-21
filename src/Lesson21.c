/*
 *		This Code Was Created By Jeff Molofee 2000
 *		If You've Found This Code Useful, Please Let Me Know.
 *		Visit My Site At nehe.gamedev.net
 *      Modified for LCCWin32 compiler by Robert Wishlaw 2002/11/24
 */

 /***************************************************************
 *  Project: $(project)
 *  Function : Main program
 ***************************************************************
 *  $Author: Jeff Molofee 2000
 *  $Name:  $
 ***************************************************************
 *
 *  Copyright NeHe Production
 *
 ***************************************************************/

/**         Comments manageable by Doxygen
*
*  Modified smoothly by Thierry DECHAIZE
*
*  Paradigm : obtain one source (only one !) compatible for multiple free C Compilers
*    and provide for all users an development environment on Windows (64 bits compatible),
*    the great Code::Blocks manager (version 20.03), and don't use glaux.lib or glaux.dll.
*
*	a) Mingw 32 bits, version officielle gcc 9.2.0 : downloadable on http://sourceforge.net/projects/mingw/ (official)
*	b) Mingw 64 bits included in new IDE Red Panda Dev-Cpp, version gcc 10.3.0 : donwloadable on http://sourceforge.net/projects/dev-cpp-2020/
*	c) Mingw 64 bits included in package Code::Blocks (version 20.03), version gcc 8.1.0 : downloadable on http://sourceforge.net/projects/codeblocks/files/Binaries/20.03/Windows/
*	d) Mingw 32 and 64 bits packagés, version gcc 11.2.0 : downloadable on  https://winlibs.com/ (and CLANG included in, 32 and 64 bits), two kits :
*			- winlibs-i686-posix-dwarf-gcc-11.2.0-llvm-13.0.0-mingw-w64ucrt-9.0.0-r2.7z (32 bits)
*			- winlibs-x86_64-posix-seh-gcc-11.2.0-llvm-13.0.0-mingw-w64ucrt-9.0.0-r2.7z (64 bits)
*	e) Cygwin64, 32 et 64 bits, version gcc 11.0.0 : downloadable on http://www.cygwin.com/install.html (tool for install : setup-x86_64.exe)
*	f) TDM GCC, 32 et 64 bits, version 10.3.0 : downloadable on http://sourceforge.net/projects/TDM-GCC
*	g) MSYS2 environnement MINGW32 and MINGW64, 32 et 64 bits, version de 2022 (msys2-x86_64-20220118.exe), version gcc 11.2.0 : downloadable on https://repo.msys2.org/distrib/x86_64/msys2-x86_64-20220118.exe
*	h) Visual Studio 2022, 32 et 64 bits, community edition for free : downloadable on https://visualstudio.microsoft.com/fr/thank-you-downloading-visual-studio/?sku=Community&rel=17
*	i) Borland C/C++ 32 bits, version 5.5 : downloadable on https://developerinsider.co/download-and-install-borland-c-compiler-on-windows-10/
*	j) Digital Mars Compiler C 32 bits version 8.57 : downloadable on http://www.digitalmars.com (the more old compiler, the more bugged, dead branch !)
*	k) OpenWatcom 32 et 64 bits, version 2.0 : downloadable on http://openwatcom.mirror.fr/ (only 32 bits version run correctly !)
*	l) Lcc and Lcc64, 32 et 64 bits: downloadable http://www.cs.virginia.edu/~lcc-win32/
*	m) PELLES C, 32 et 64 bits, version 11.0 : downloadable on http://www.smorgasbordet.com/pellesc/
*	o) CLANG, adossé aux environnements MINGW64 et MINGW32, version 13.0.0 (version gcc 12.0.0) : downloadable on https://winlibs.com/
*	p) CLANG, adossé aux environnements Visual Studio 2022 (+ kits Microsoft), version 13.0.0 : downloadable on https://releases.llvm.org/download.html
*	q) CLANG de la version MSYS2, adossé aux environnements MINGW64 et MINGW32, version 13.0.0 (version gcc 11.2.0) : downloadable on https://repo.msys2.org/distrib/x86_64/msys2-x86_64-20220118.exe
*	r) CLANG de la version CYGWIN, adossé aux environnements MINGW64 et MINGW32, version 8.0.0 (version gcc 11.0.0) : downloadable http://www.cygwin.com/install.html (tool for install : setup-x86_64.exe)
*
*   TDE -> Add resource file and resource header for restitute version + icon OpenGL.ico for fun
*			because versionning is important, same for freeware :-) !
*
*  Date : 2022/02/15
*
* \file            Lesson21.c
* \author          Jeff Molofee ( NeHe ) originely, Modified for LCCWin32 compiler by Robert Wishlaw 2002/11/23
* \author          After adapted by Thierry Dechaize to verify paradigm : one source for multiple C Compilers
* \version         2.0.1.0
* \date            15 février 2022
* \brief           Ouvre une fenêtre Windows et dessine une trame de lignes pour émuler un jeu proche de pacman (simplifié).
* \details         Ce programme ne gére que trois événements : le clic sur le bouton "Fermé" de la fenêtre, la sortie par la touche ESC et les flêches de déplacement clavier.
*
*
*/

#if defined __CYGWIN__ || defined __LCC__
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>								// Header File For Windows
#if defined(__LCC__)
#ifndef WINGDIAPI
#   define WINGDIAPI __stdcall
#endif
#endif

#include <stdio.h>									// Header File For Standard Input / Output
#include <stdarg.h>									// Header File For Variable Argument Routines
#include <gl\gl.h>									// Header File For The OpenGL32 Library
#include <gl\glu.h>									// Header File For The GLu32 Library
/* #include <gl\glaux.h>		                    // Header File For The Glaux Library   (NEW) */

#if defined __POCC__ || defined __LCC__     // because "rand" function declared in it ... !!!`
#include <stdlib.h>
#endif

#if defined __LCC__ || defined __CYGWIN__ || defined __POCC__          // LCC and CYGWIN needs this header File For timeGetTime
#include <mmsystem.h>
#endif

#if defined __GNUC__ || defined __LCC__ || defined _MSC_VER || defined __TURBOC__
#include <stdbool.h>
#endif

#if defined(__SC__) || defined(__DMC__)
#include <wtypes.h>
// typedef BOOLEAN         bool;
#endif

// A user defined ``bool'' type for compilers that don't yet support one.
//
#if defined(__BORLANDC__) && (__BORLANDC__ < 0x500) || defined(__WATCOMC__)
  #define DONT_HAVE_BOOL_TYPE
#endif

// A ``bool'' type for compilers that don't yet support one.
#if defined(DONT_HAVE_BOOL_TYPE)
  typedef char bool;

  #ifdef true
    #warning Better check include file ``mytypes.h''.
    #undef true
  #endif
  #define true 1

  #ifdef false
    #warning Better check include file ``mytypes.h''.
    #undef false
  #endif
  #define false 0
#endif

HDC			hDC=NULL;										// Private GDI Device Context
HGLRC		hRC=NULL;										// Permanent Rendering Context
HWND		hWnd=NULL;										// Holds Our Window Handle
HINSTANCE	hInstance;										// Holds The Instance Of The Application

BOOL	keys[256];											// Array Used For The Keyboard Routine
BOOL	vline[11][10];										// Keeps Track Of Verticle Lines
BOOL	hline[10][11];										// Keeps Track Of Horizontal Lines
BOOL	ap;													// 'A' Key Pressed?
BOOL	filled;												// Done Filling In The Grid?
BOOL	gameover;											// Is The Game Over?
BOOL	anti=TRUE;											// Antialiasing?
BOOL	active=TRUE;										// Window Active Flag Set To TRUE By Default
BOOL	fullscreen=TRUE;									// Fullscreen Flag Set To Fullscreen Mode By Default

int		loop1;												// Generic Loop1
int		loop2;												// Generic Loop2
int		delay;												// Enemy Delay
int		adjust=3;											// Speed Adjustment For Really Slow Video Cards
int		lives=5;											// Player Lives
int		level=1;											// Internal Game Level
int		level2=1;	    									// Displayed Game Level
int		stage=1;											// Game Stage

struct	object												// Create A Structure For Our Player
{
	int		fx, fy;											// Fine Movement Position
	int		x, y;											// Current Player Position
	float	spin;											// Spin Direction
};

struct	object player;										// Player Information
struct	object enemy[9];									// Enemy Information
struct	object hourglass;									// Hourglass Information

struct			 											// Create A Structure For The Timer Information
{
  __int64       frequency;									// Timer Frequency
  float         resolution;									// Timer Resolution
  unsigned long mm_timer_start;								// Multimedia Timer Start Value
  unsigned long mm_timer_elapsed;							// Multimedia Timer Elapsed Time
  BOOL			performance_timer;							// Using The Performance Timer?
  __int64       performance_timer_start;					// Performance Timer Start Value
  __int64       performance_timer_elapsed;					// Performance Timer Elapsed Time
} timer;													// Structure Is Named timer

int		steps[6]={ 1, 2, 4, 5, 10, 20 };					// Stepping Values For Slow Video Adjustment

GLuint	texture[2];											// Font Texture Storage Space
GLuint	base;												// Base Display List For The Font

static	PIXELFORMATDESCRIPTOR pfd=							// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),							// Size Of This Pixel Format Descriptor
		1,														// Version Number
		PFD_DRAW_TO_WINDOW |									// Format Must Support Window
		PFD_SUPPORT_OPENGL |									// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,										// Must Support Double Buffering
		PFD_TYPE_RGBA,											// Request An RGBA Format
		0,  													// Select Our Color Depth
		0, 0, 0, 0, 0, 0,										// Color Bits Ignored
		0,														// No Alpha Buffer
		0,														// Shift Bit Ignored
		0,														// No Accumulation Buffer
		0, 0, 0, 0,												// Accumulation Bits Ignored
		16,														// 16Bit Z-Buffer (Depth Buffer)
		0,														// No Stencil Buffer
		0,														// No Auxiliary Buffer
		PFD_MAIN_PLANE,											// Main Drawing Layer
		0,														// Reserved
		0, 0, 0													// Layer Masks Ignored
    };

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);		// Declaration For WndProc

/**	            This Code initialize Timer.
*
* \brief      Fonction TimerInit : Initialisation du timer
* \details    Rien
* \param	  void			        un void, aucun paramètre				                            *
* \return     void			        un void, aucun retour                                               *
*
*/

void TimerInit(void)										// Initialize Our Timer (Get It Ready)
{
	memset(&timer, 0, sizeof(timer));						// Clear Our Timer Structure

	// Check To See If A Performance Counter Is Available
	// If One Is Available The Timer Frequency Will Be Updated
	if (!QueryPerformanceFrequency((LARGE_INTEGER *) &timer.frequency))
	{
		// No Performace Counter Available
		timer.performance_timer	= FALSE;					// Set Performance Timer To FALSE
		timer.mm_timer_start	= timeGetTime();			// Use timeGetTime() To Get Current Time
		timer.resolution		= 1.0f/1000.0f;				// Set Our Timer Resolution To .001f
		timer.frequency			= 1000;						// Set Our Timer Frequency To 1000
		timer.mm_timer_elapsed	= timer.mm_timer_start;		// Set The Elapsed Time To The Current Time
	}
	else
	{
		// Performance Counter Is Available, Use It Instead Of The Multimedia Timer
		// Get The Current Time And Store It In performance_timer_start
		QueryPerformanceCounter((LARGE_INTEGER *) &timer.performance_timer_start);
		timer.performance_timer			= TRUE;				// Set Performance Timer To TRUE
		// Calculate The Timer Resolution Using The Timer Frequency
		timer.resolution				= (float) (((double)1.0f)/((double)timer.frequency));
		// Set The Elapsed Time To The Current Time
		timer.performance_timer_elapsed	= timer.performance_timer_start;
	}
}

/**	            This Code recupére le temps du timer.
*
* \brief      Fonction TimerGetTime : recupération du temps du timer
* \details    Rien
* \return     float			        le temps récupéré                                                   *
*
*/

float TimerGetTime()										// Get Time In Milliseconds
{
	__int64 time;											// time Will Hold A 64 Bit Integer

	if (timer.performance_timer)							// Are We Using The Performance Timer?
	{
		QueryPerformanceCounter((LARGE_INTEGER *) &time);	// Grab The Current Performance Time
		// Return The Current Time Minus The Start Time Multiplied By The Resolution And 1000 (To Get MS)
		return ( (float) ( time - timer.performance_timer_start) * timer.resolution)*1000.0f;
	}
	else
	{
		// Return The Current Time Minus The Start Time Multiplied By The Resolution And 1000 (To Get MS)
		return( (float) ( timeGetTime() - timer.mm_timer_start) * timer.resolution)*1000.0f;
	}
}

/**	            This Code reset all objects.
*
* \brief      Fonction ResetObjects : reset of all objects used in this code
* \details    Rien
* \param	  void			        un void, aucun paramètre				                            *
* \return     void			        un void, aucun retour                                               *
*
*/

void ResetObjects(void)										// Reset Player And Enemies
{
	player.x=0;												// Reset Player X Position To Far Left Of The Screen
	player.y=0;												// Reset Player Y Position To The Top Of The Screen
	player.fx=0;											// Set Fine X Position To Match
	player.fy=0;											// Set Fine Y Position To Match

	for (loop1=0; loop1<(stage*level); loop1++)				// Loop Through All The Enemies
	{
		enemy[loop1].x=5+rand()%6;							// Select A Random X Position
		enemy[loop1].y=rand()%11;							// Select A Random Y Position
		enemy[loop1].fx=enemy[loop1].x*60;					// Set Fine X To Match
		enemy[loop1].fy=enemy[loop1].y*40;					// Set Fine Y To Match
	}
}

/**	            This Code Creates Texture From a Bitmap File.
*
* \brief      Fonction NeHeLoadBitmap2 : charge un fichier BMP en mémoire pour generer un tableau de deux textures
* \details    En entrée le nom du fichier Bitmap et en sortie le tableau des deux textures utilisables avec OpenGL
* \param	  szFileName1			nom du premier fichier BMP				                            *
* \param	  szFileName2			nom du deuxième fichier BMP				                            *
* \param	  *texid			    un pointeur sur le tableau des deux textures générées			    *
* \return     bool                  un booleen, le tableau des deux textures créé ou non.               *
*
*/

bool NeHeLoadBitmap2(LPTSTR szFileName1, LPTSTR szFileName2, GLuint *texid)					// Creates Texture From A Bitmap File
{
	HBITMAP hBMP1, hBMP2;														// Handle Of The Bitmap
	BITMAP	BMP1, BMP2;														// Bitmap Structure

    glGenTextures(2, &texid[0]);					                    // Create Three Textures

	hBMP1=(HBITMAP)LoadImage(GetModuleHandle(NULL), szFileName1, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE );

	if (!hBMP1)															// Does The Bitmap Exist?
		return FALSE;													// If Not Return False

	// Get The Object
	GetObject(hBMP1, sizeof(BMP1), &BMP1);								// hBMP:        Handle To Graphics Object
																		// sizeof(BMP): Size Of Buffer For Object Information
																		// &BMP:        Buffer For Object Information
	hBMP2=(HBITMAP)LoadImage(GetModuleHandle(NULL), szFileName2, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE );

	if (!hBMP2)															// Does The Bitmap Exist?
		return FALSE;													// If Not Return False

	// Get The Object
	GetObject(hBMP2, sizeof(BMP2), &BMP2);								// hBMP:        Handle To Graphics Object
																		// sizeof(BMP): Size Of Buffer For Object Information
																		// &BMP:        Buffer For Object Information
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);								// Pixel Storage Mode (Word Alignment / 4 Bytes)

    // Create Linear Filtered Texture
    glBindTexture(GL_TEXTURE_2D, texid[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, BMP1.bmWidth, BMP1.bmHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, BMP1.bmBits);

    // Create Linear Filtered Texture
    glBindTexture(GL_TEXTURE_2D, texid[1]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, BMP2.bmWidth, BMP2.bmHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, BMP2.bmBits);

	DeleteObject(hBMP1);													// Delete The Object
	DeleteObject(hBMP2);													// Delete The Object

	return TRUE;														// Loading Was Successful
}

int LoadGLTextures()										// Load Bitmaps And Convert To Textures
{
	// Start Of User Initialization
	if (!NeHeLoadBitmap2("../../Data/Font1.bmp","../../Data/Image.bmp", texture))		// Load The Bitmap
		return FALSE;

	return TRUE;											// Return The Status
}

/**	            This Code Create la fonte à afficher.
*
* \brief      Fonction BuildFont : création de la fonte du texte à afficher
* \details    Cette fonction utilise la fonction CreateFont
* \param      GLvoid        un void OpenGL.
* \return     GLvoid        un void OpenGL.
*
*/

GLvoid BuildFont(GLvoid)									// Build Our Font Display List
{
	base=glGenLists(256);									// Creating 256 Display Lists
	glBindTexture(GL_TEXTURE_2D, texture[0]);				// Select Our Font Texture
	for (loop1=0; loop1<256; loop1++)						// Loop Through All 256 Lists
	{
		float cx=(float)(loop1%16)/16.0f;						// X Position Of Current Character
		float cy=(float)(loop1/16)/16.0f;						// Y Position Of Current Character

		glNewList(base+loop1,GL_COMPILE);					// Start Building A List
			glBegin(GL_QUADS);								// Use A Quad For Each Character
				glTexCoord2f(cx,1.0f-cy-0.0625f);			// Texture Coord (Bottom Left)
				glVertex2d(0,16);							// Vertex Coord (Bottom Left)
				glTexCoord2f(cx+0.0625f,1.0f-cy-0.0625f);	// Texture Coord (Bottom Right)
				glVertex2i(16,16);							// Vertex Coord (Bottom Right)
				glTexCoord2f(cx+0.0625f,1.0f-cy);			// Texture Coord (Top Right)
				glVertex2i(16,0);							// Vertex Coord (Top Right)
				glTexCoord2f(cx,1.0f-cy);					// Texture Coord (Top Left)
				glVertex2i(0,0);							// Vertex Coord (Top Left)
			glEnd();										// Done Building Our Quad (Character)
			glTranslated(15,0,0);							// Move To The Right Of The Character
		glEndList();										// Done Building The Display List
	}														// Loop Until All 256 Are Built
}

/**	            This Code destruct la fonte à afficher.
*
* \brief      Fonction KillFont : descruction de la fonte
* \details    Cette fonction détruit l'ensemble des 96 caractères de la fonte
* \param      GLvoid        un void OpenGL.
* \return     GLvoid        un void OpenGL.
*
*/

GLvoid KillFont(GLvoid)										// Delete The Font From Memory
{
	glDeleteLists(base,256);								// Delete All 256 Display Lists
}

/**	            This Code presente la fonte à afficher.
*
* \brief      Fonction glPrint : impression à l'écran de la fonte
* \details    Cette fonction affiche l'ensemble des 96 caractères de la fonte
* \param      x             un entier OpenGL (GLint).
* \param      y             un autre entier OpenGL (GLint).
* \param      set           un entier représentant un ensemble.
* \param      *fmt          un pointeur sur la chaîne de caractères.
* \param      ...           une liste indéterminée de paramètres
* \return     GLvoid        un void OpenGL.
*
*/

GLvoid glPrint(GLint x, GLint y, int set, const char *fmt, ...)	// Where The Printing Happens
{
	char		text[256];									// Holds Our String
	va_list		ap;											// Pointer To List Of Arguments

	if (fmt == NULL)										// If There's No Text
		return;												// Do Nothing

	va_start(ap, fmt);										// Parses The String For Variables
	    vsprintf(text, fmt, ap);							// And Converts Symbols To Actual Numbers
	va_end(ap);												// Results Are Stored In Text

	if (set>1)												// Did User Choose An Invalid Character Set?
	{
		set=1;												// If So, Select Set 1 (Italic)
	}
	glEnable(GL_TEXTURE_2D);								// Enable Texture Mapping
	glLoadIdentity();										// Reset The Modelview Matrix
	glTranslated(x,y,0);									// Position The Text (0,0 - Bottom Left)
	glListBase(base-32+(128*set));							// Choose The Font Set (0 or 1)

	if (set==0)												// If Set 0 Is Being Used Enlarge Font
	{
		glScalef(1.5f,2.0f,1.0f);							// Enlarge Font Width And Height
	}

	glCallLists(strlen(text),GL_UNSIGNED_BYTE, text);		// Write The Text To The Screen
	glDisable(GL_TEXTURE_2D);								// Disable Texture Mapping
}

/**	            This Code Resize the main window.
*
* \brief      Fonction ReSizeGLScene : redimensionnement de la fenêtre Windows gérant OpenGL
* \details    En entrée les deux nouvelles dimensions de la fenêtre
* \param	  width			Width of the GL Window Or Fullscreen Mode				*
* \param	  height		Height of the GL Window Or Fullscreen Mode			    *
* \return     GLvoid        un void OpenGL.
*
*/

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)			// Resize And Initialize The GL Window
{
	if (height==0)											// Prevent A Divide By Zero By
	{
		height=1;											// Making Height Equal One
	}

	glViewport(0,0,width,height);							// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);							// Select The Projection Matrix
	glLoadIdentity();										// Reset The Projection Matrix

	glOrtho(0.0f,width,height,0.0f,-1.0f,1.0f);				// Create Ortho 640x480 View (0,0 At Top Left)

	glMatrixMode(GL_MODELVIEW);								// Select The Modelview Matrix
	glLoadIdentity();										// Reset The Modelview Matrix
}

/**	            This Code finish the initialization OpenGL of the main window.
*
* \brief      Fonction InitGL : Fin de l'initialisation de la fenêtre Windows gérant OpenGL
* \details    Rien de spécial
* \param	  GLvoid		un void OpenGL.
* \return     int        	un entier (booleen)
*
*/

int InitGL(GLvoid)											// All Setup For OpenGL Goes Here
{
	if (!LoadGLTextures())									// Jump To Texture Loading Routine
	{
		return FALSE;										// If Texture Didn't Load Return FALSE
	}

	BuildFont();											// Build The Font

	glShadeModel(GL_SMOOTH);								// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);					// Black Background
	glClearDepth(1.0f);										// Depth Buffer Setup
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);					// Set Line Antialiasing
	glEnable(GL_BLEND);										// Enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);		// Type Of Blending To Use
	return TRUE;											// Initialization Went OK
}

/**	            This Code draw the scene OpenGL in the main window.
*
* \brief      Fonction DrawGLScene : Dessin sous OpenGL dans la fenêtre Windows.
* \details    Rien de spécial
* \param	  GLvoid		un void OpenGL.
* \return     int        	un entier (booleen)
*
*/

int DrawGLScene(GLvoid)										// Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
	glBindTexture(GL_TEXTURE_2D, texture[0]);				// Select Our Font Texture
	glColor3f(1.0f,0.5f,1.0f);								// Set Color To Purple
	glPrint(207,24,0,"GRID CRAZY");							// Write GRID CRAZY On The Screen
	glColor3f(1.0f,1.0f,0.0f);								// Set Color To Yellow
	glPrint(20,20,1,"Level:%2i",level2);					// Write Actual Level Stats
	glPrint(20,40,1,"Stage:%2i",stage);						// Write Stage Stats

	if (gameover)											// Is The Game Over?
	{
		glColor3ub(rand()%255,rand()%255,rand()%255);		// Pick A Random Color
		glPrint(472,20,1,"GAME OVER");						// Write GAME OVER To The Screen
		glPrint(456,40,1,"PRESS SPACE");					// Write PRESS SPACE To The Screen
	}

	for (loop1=0; loop1<lives-1; loop1++)					// Loop Through Lives Minus Current Life
	{
		glLoadIdentity();									// Reset The View
		glTranslatef(490+(loop1*40.0f),40.0f,0.0f);			// Move To The Right Of Our Title Text
		glRotatef(-player.spin,0.0f,0.0f,1.0f);				// Rotate Counter Clockwise
		glColor3f(0.0f,1.0f,0.0f);							// Set Player Color To Light Green
		glBegin(GL_LINES);									// Start Drawing Our Player Using Lines
			glVertex2d(-5,-5);								// Top Left Of Player
			glVertex2d( 5, 5);								// Bottom Right Of Player
			glVertex2d( 5,-5);								// Top Right Of Player
			glVertex2d(-5, 5);								// Bottom Left Of Player
		glEnd();											// Done Drawing The Player
		glRotatef(-player.spin*0.5f,0.0f,0.0f,1.0f);		// Rotate Counter Clockwise
		glColor3f(0.0f,0.75f,0.0f);							// Set Player Color To Dark Green
		glBegin(GL_LINES);									// Start Drawing Our Player Using Lines
			glVertex2d(-7, 0);								// Left Center Of Player
			glVertex2d( 7, 0);								// Right Center Of Player
			glVertex2d( 0,-7);								// Top Center Of Player
			glVertex2d( 0, 7);								// Bottom Center Of Player
		glEnd();											// Done Drawing The Player
	}

	filled=TRUE;											// Set Filled To True Before Testing
	glLineWidth(2.0f);										// Set Line Width For Cells To 2.0f
	glDisable(GL_LINE_SMOOTH);								// Disable Antialiasing
	glLoadIdentity();										// Reset The Current Modelview Matrix
	for (loop1=0; loop1<11; loop1++)						// Loop From Left To Right
	{
		for (loop2=0; loop2<11; loop2++)					// Loop From Top To Bottom
		{
			glColor3f(0.0f,0.5f,1.0f);						// Set Line Color To Blue
			if (hline[loop1][loop2])						// Has The Horizontal Line Been Traced
			{
				glColor3f(1.0f,1.0f,1.0f);					// If So, Set Line Color To White
			}

			if (loop1<10)									// Dont Draw To Far Right
			{
				if (!hline[loop1][loop2])					// If A Horizontal Line Isn't Filled
				{
					filled=FALSE;							// filled Becomes False
				}
				glBegin(GL_LINES);							// Start Drawing Horizontal Cell Borders
					glVertex2d(20+(loop1*60),70+(loop2*40));// Left Side Of Horizontal Line
					glVertex2d(80+(loop1*60),70+(loop2*40));// Right Side Of Horizontal Line
				glEnd();									// Done Drawing Horizontal Cell Borders
			}

			glColor3f(0.0f,0.5f,1.0f);						// Set Line Color To Blue
			if (vline[loop1][loop2])						// Has The Horizontal Line Been Traced
			{
				glColor3f(1.0f,1.0f,1.0f);					// If So, Set Line Color To White
			}
			if (loop2<10)									// Dont Draw To Far Down
			{
				if (!vline[loop1][loop2])					// If A Verticle Line Isn't Filled
				{
					filled=FALSE;							// filled Becomes False
				}
				glBegin(GL_LINES);							// Start Drawing Verticle Cell Borders
					glVertex2d(20+(loop1*60),70+(loop2*40));// Left Side Of Horizontal Line
					glVertex2d(20+(loop1*60),110+(loop2*40));// Right Side Of Horizontal Line
				glEnd();									// Done Drawing Verticle Cell Borders
			}

			glEnable(GL_TEXTURE_2D);						// Enable Texture Mapping
			glColor3f(1.0f,1.0f,1.0f);						// Bright White Color
			glBindTexture(GL_TEXTURE_2D, texture[1]);		// Select The Tile Image
			if ((loop1<10) && (loop2<10))					// If In Bounds, Fill In Traced Boxes
			{
				// Are All Sides Of The Box Traced?
				if (hline[loop1][loop2] && hline[loop1][loop2+1] && vline[loop1][loop2] && vline[loop1+1][loop2])
				{
					glBegin(GL_QUADS);						// Draw A Textured Quad
						glTexCoord2f((float)(loop1/10.0f)+0.1f,1.0f-((float)(loop2/10.0f)));
						glVertex2d(20+(loop1*60)+59,(70+loop2*40+1));	// Top Right
						glTexCoord2f((float)(loop1/10.0f),1.0f-((float)(loop2/10.0f)));
						glVertex2d(20+(loop1*60)+1,(70+loop2*40+1));	// Top Left
						glTexCoord2f((float)(loop1/10.0f),1.0f-((float)(loop2/10.0f)+0.1f));
						glVertex2d(20+(loop1*60)+1,(70+loop2*40)+39);	// Bottom Left
						glTexCoord2f((float)(loop1/10.0f)+0.1f,1.0f-((float)(loop2/10.0f)+0.1f));
						glVertex2d(20+(loop1*60)+59,(70+loop2*40)+39);	// Bottom Right
					glEnd();								// Done Texturing The Box
				}
			}
			glDisable(GL_TEXTURE_2D);						// Disable Texture Mapping
		}
	}
	glLineWidth(1.0f);										// Set The Line Width To 1.0f

	if (anti)												// Is Anti TRUE?
	{
		glEnable(GL_LINE_SMOOTH);							// If So, Enable Antialiasing
	}

	if (hourglass.fx==1)									// If fx=1 Draw The Hourglass
	{
		glLoadIdentity();									// Reset The Modelview Matrix
		glTranslatef(20.0f+(hourglass.x*60),70.0f+(hourglass.y*40),0.0f);	// Move To The Fine Hourglass Position
		glRotatef(hourglass.spin,0.0f,0.0f,1.0f);			// Rotate Clockwise
		glColor3ub(rand()%255,rand()%255,rand()%255);		// Set Hourglass Color To Random Color
		glBegin(GL_LINES);									// Start Drawing Our Hourglass Using Lines
			glVertex2d(-5,-5);								// Top Left Of Hourglass
			glVertex2d( 5, 5);								// Bottom Right Of Hourglass
			glVertex2d( 5,-5);								// Top Right Of Hourglass
			glVertex2d(-5, 5);								// Bottom Left Of Hourglass
			glVertex2d(-5, 5);								// Bottom Left Of Hourglass
			glVertex2d( 5, 5);								// Bottom Right Of Hourglass
			glVertex2d(-5,-5);								// Top Left Of Hourglass
			glVertex2d( 5,-5);								// Top Right Of Hourglass
		glEnd();											// Done Drawing The Hourglass
	}

	glLoadIdentity();										// Reset The Modelview Matrix
	glTranslatef(player.fx+20.0f,player.fy+70.0f,0.0f);		// Move To The Fine Player Position
	glRotatef(player.spin,0.0f,0.0f,1.0f);					// Rotate Clockwise
	glColor3f(0.0f,1.0f,0.0f);								// Set Player Color To Light Green
	glBegin(GL_LINES);										// Start Drawing Our Player Using Lines
		glVertex2d(-5,-5);									// Top Left Of Player
		glVertex2d( 5, 5);									// Bottom Right Of Player
		glVertex2d( 5,-5);									// Top Right Of Player
		glVertex2d(-5, 5);									// Bottom Left Of Player
	glEnd();												// Done Drawing The Player
	glRotatef(player.spin*0.5f,0.0f,0.0f,1.0f);				// Rotate Clockwise
	glColor3f(0.0f,0.75f,0.0f);								// Set Player Color To Dark Green
	glBegin(GL_LINES);										// Start Drawing Our Player Using Lines
		glVertex2d(-7, 0);									// Left Center Of Player
		glVertex2d( 7, 0);									// Right Center Of Player
		glVertex2d( 0,-7);									// Top Center Of Player
		glVertex2d( 0, 7);									// Bottom Center Of Player
	glEnd();												// Done Drawing The Player

	for (loop1=0; loop1<(stage*level); loop1++)				// Loop To Draw Enemies
	{
		glLoadIdentity();									// Reset The Modelview Matrix
		glTranslatef(enemy[loop1].fx+20.0f,enemy[loop1].fy+70.0f,0.0f);
		glColor3f(1.0f,0.5f,0.5f);							// Make Enemy Body Pink
		glBegin(GL_LINES);									// Start Drawing Enemy
			glVertex2d( 0,-7);								// Top Point Of Body
			glVertex2d(-7, 0);								// Left Point Of Body
			glVertex2d(-7, 0);								// Left Point Of Body
			glVertex2d( 0, 7);								// Bottom Point Of Body
			glVertex2d( 0, 7);								// Bottom Point Of Body
			glVertex2d( 7, 0);								// Right Point Of Body
			glVertex2d( 7, 0);								// Right Point Of Body
			glVertex2d( 0,-7);								// Top Point Of Body
		glEnd();											// Done Drawing Enemy Body
		glRotatef(enemy[loop1].spin,0.0f,0.0f,1.0f);		// Rotate The Enemy Blade
		glColor3f(1.0f,0.0f,0.0f);							// Make Enemy Blade Red
		glBegin(GL_LINES);									// Start Drawing Enemy Blade
			glVertex2d(-7,-7);								// Top Left Of Enemy
			glVertex2d( 7, 7);								// Bottom Right Of Enemy
			glVertex2d(-7, 7);								// Bottom Left Of Enemy
			glVertex2d( 7,-7);								// Top Right Of Enemy
		glEnd();											// Done Drawing Enemy Blade
	}
	return TRUE;											// Everything Went OK
}

/**	            This Code destroy all resources of this program.
*
* \brief      Fonction KillGLWindow : Destruction de toutes les ressources du programme.
* \details    Rien de spécial
* \param	  GLvoid			un void OpenGL.
* \return     GLvoid        	un void OpenGL.
*
*/

GLvoid KillGLWindow(GLvoid)									// Properly Kill The Window
{
	if (fullscreen)											// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);						// If So Switch Back To The Desktop
		ShowCursor(TRUE);									// Show Mouse Pointer
	}

	if (hRC)												// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))						// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))							// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;											// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))						// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;											// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))						// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;											// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))				// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;										// Set hInstance To NULL
	}

	KillFont();												// Kill The Font We Built
}

/**				This Code Creates Our OpenGL Window.
 *  \brief          Creation of our OpenGL Window
 *  \param 			title			- Title To Appear At The Top Of The Window				*
 *	\param 			width			- Width Of The GL Window Or Fullscreen Mode				*
 *	\param 			height			- Height Of The GL Window Or Fullscreen Mode			*
 *	\param          bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	\param          fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*
 *  \return         BOOL            - un entier booleen (OK ou non).             			*
 */

BOOL CreateGLWindow(char* title, int width, int height, int bits, BOOL fullscreenflag)
{
	GLuint		PixelFormat;									// Holds The Results After Searching For A Match
	WNDCLASS	wc;												// Windows Class Structure
	DWORD		dwExStyle;										// Window Extended Style
	DWORD		dwStyle;										// Window Style
	RECT		WindowRect;										// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;									// Set Left Value To 0
	WindowRect.right=(long)width;								// Set Right Value To Requested Width
	WindowRect.top=(long)0;										// Set Top Value To 0
	WindowRect.bottom=(long)height;								// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;									// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;								// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);	// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,						// Extended Style For The Window
								"OpenGL",						// Class Name
								title,							// Window Title
								dwStyle |						// Defined Window Style
								WS_CLIPSIBLINGS |				// Required Window Style
								WS_CLIPCHILDREN,				// Required Window Style
								0, 0,							// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,							// No Parent Window
								NULL,							// No Menu
								hInstance,						// Instance
								NULL)))							// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();											// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

    pfd.cColorBits = bits;

    if (!(hDC=GetDC(hWnd)))                         // Did We Get A Device Context?
	{
		KillGLWindow();											// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))				// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();											// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))					// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();											// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))							// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();											// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))								// Try To Activate The Rendering Context
	{
		KillGLWindow();											// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);									// Show The Window
	SetForegroundWindow(hWnd);									// Slightly Higher Priority
	SetFocus(hWnd);												// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);								// Set Up Our Perspective GL Screen

	if (!InitGL())												// Initialize Our Newly Created GL Window
	{
		KillGLWindow();											// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	return TRUE;												// Success
}

/**         Comments manageable by Doxygen
*
* \brief      Fonction CALLBACK de traitement des messages Windows
* \details    Traitement de la boucle infinie des messages Windows
* \param      hWnd         L'header de la fenêtre principale.
* \param      uMsg         Un entier non signé.
* \param      wParam       Les paramétres en entrée.
* \param      lParam       Autres paramétres en entrée.
* \return     LRESULT 	   Un LRESULT donnant le status du traitement du message.
*
*/

LRESULT CALLBACK WndProc(	HWND	hWnd,						// Handle For This Window
							UINT	uMsg,						// Message For This Window
							WPARAM	wParam,						// Additional Message Information
							LPARAM	lParam)						// Additional Message Information
{
	switch (uMsg)												// Check For Windows Messages
	{
		case WM_ACTIVATE:										// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))								// Check Minimization State
			{
				active=TRUE;									// Program Is Active
			}
			else												// Otherwise
			{
				active=FALSE;									// Program Is No Longer Active
			}

			return 0;											// Return To The Message Loop
		}

		case WM_SYSCOMMAND:										// Intercept System Commands
		{
			switch (wParam)										// Check System Calls
			{
				case SC_SCREENSAVE:								// Screensaver Trying To Start?
				case SC_MONITORPOWER:							// Monitor Trying To Enter Powersave?
				return 0;										// Prevent From Happening
			}
			break;												// Exit
		}

		case WM_CLOSE:											// Did We Receive A Close Message?
		{
			PostQuitMessage(0);									// Send A Quit Message
			return 0;											// Jump Back
		}

		case WM_KEYDOWN:										// Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;								// If So, Mark It As TRUE
			return 0;											// Jump Back
		}

		case WM_KEYUP:											// Has A Key Been Released?
		{
			keys[wParam] = FALSE;								// If So, Mark It As FALSE
			return 0;											// Jump Back
		}

		case WM_SIZE:											// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));		// LoWord=Width, HiWord=Height
			return 0;											// Jump Back
		}
	}

	return DefWindowProc(hWnd,uMsg,wParam,lParam);				// Pass All Unhandled Messages To DefWindowProc
}

/**	This Code is mandatory to create windows application (function WinMain)					*
 *  \brief          Creation of our application on Windows System (not console application) *
 *  \param 			hInstance		- Header de l'instance Windows				            *
 *	\param 			hPrevInstance	- Header de l'instance précédente de Windows 			*
 *	\param 			lpCmdLine		- Un pointeur sur la ligne de commande 			        *
 *	\param          nCmdShow		- Un indicateur d'état			                        *
 *  \return         int             - un entier booleen (OK ou non).                        *
 *	                                                                                        *
 */

int WINAPI WinMain(	HINSTANCE	hInstance,						// Instance
					HINSTANCE	hPrevInstance,					// Previous Instance
					LPSTR		lpCmdLine,						// Command Line Parameters
					int			nCmdShow)						// Window Show State
{
	MSG		msg;												// Windows Message Structure
	BOOL	done=FALSE;											// BOOL Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;										// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("NeHe's Line Tutorial",640,480,16,fullscreen))
	{
		return 0;												// Quit If Window Was Not Created
	}

	ResetObjects();												// Set Player / Enemy Starting Positions
	TimerInit();

	while(!done)												// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))				// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)							// Have We Received A Quit Message?
			{
				done=TRUE;										// If So done=TRUE
			}
			else												// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);							// Translate The Message
				DispatchMessage(&msg);							// Dispatch The Message
			}
		}
		else													// If There Are No Messages
		{
			float start=TimerGetTime();							// Grab Timer Value Before We Draw

			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if ((active && !DrawGLScene()) || keys[VK_ESCAPE])	// Active?  Was There A Quit Received?
			{
				done=TRUE;										// ESC or DrawGLScene Signalled A Quit
			}
			else												// Not Time To Quit, Update Screen
			{
				SwapBuffers(hDC);								// Swap Buffers (Double Buffering)
			}

			while(TimerGetTime()<start+(float)(steps[adjust]*2.0f)) {}	// Waste Cycles On Fast Systems

			if (keys[VK_F1])									// Is F1 Being Pressed?
			{
				keys[VK_F1]=FALSE;								// If So Make Key FALSE
				KillGLWindow();									// Kill Our Current Window
				fullscreen=!fullscreen;							// Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				if (!CreateGLWindow("NeHe's Line Tutorial",640,480,16,fullscreen))
				{
					return 0;									// Quit If Window Was Not Created
				}
			}

			if (keys['A'] && !ap)								// If 'A' Key Is Pressed And Not Held
			{
				ap=TRUE;										// ap Becomes TRUE
				anti=!anti;										// Toggle Antialiasing
			}
			if (!keys['A'])										// If 'A' Key Has Been Released
			{
				ap=FALSE;										// ap Becomes FALSE
			}

			if (!gameover && active)							// If Game Isn't Over And Programs Active Move Objects
			{
				for (loop1=0; loop1<(stage*level); loop1++)		// Loop Through The Different Stages
				{
					if ((enemy[loop1].x<player.x) && (enemy[loop1].fy==enemy[loop1].y*40))
					{
						enemy[loop1].x++;						// Move The Enemy Right
					}

					if ((enemy[loop1].x>player.x) && (enemy[loop1].fy==enemy[loop1].y*40))
					{
						enemy[loop1].x--;						// Move The Enemy Left
					}

					if ((enemy[loop1].y<player.y) && (enemy[loop1].fx==enemy[loop1].x*60))
					{
						enemy[loop1].y++;						// Move The Enemy Down
					}

					if ((enemy[loop1].y>player.y) && (enemy[loop1].fx==enemy[loop1].x*60))
					{
						enemy[loop1].y--;						// Move The Enemy Up
					}

					if (delay>(3-level) && (hourglass.fx!=2))	// If Our Delay Is Done And Player Doesn't Have Hourglass
					{
						delay=0;								// Reset The Delay Counter Back To Zero
						for (loop2=0; loop2<(stage*level); loop2++)	// Loop Through All The Enemies
						{
							if (enemy[loop2].fx<enemy[loop2].x*60)	// Is Fine Position On X Axis Lower Than Intended Position?
							{
								enemy[loop2].fx+=steps[adjust];	// If So, Increase Fine Position On X Axis
								enemy[loop2].spin+=steps[adjust];	// Spin Enemy Clockwise
							}
							if (enemy[loop2].fx>enemy[loop2].x*60)	// Is Fine Position On X Axis Higher Than Intended Position?
							{
								enemy[loop2].fx-=steps[adjust];	// If So, Decrease Fine Position On X Axis
								enemy[loop2].spin-=steps[adjust];	// Spin Enemy Counter Clockwise
							}
							if (enemy[loop2].fy<enemy[loop2].y*40)	// Is Fine Position On Y Axis Lower Than Intended Position?
							{
								enemy[loop2].fy+=steps[adjust];	// If So, Increase Fine Position On Y Axis
								enemy[loop2].spin+=steps[adjust];	// Spin Enemy Clockwise
							}
							if (enemy[loop2].fy>enemy[loop2].y*40)	// Is Fine Position On Y Axis Higher Than Intended Position?
							{
								enemy[loop2].fy-=steps[adjust];	// If So, Decrease Fine Position On Y Axis
								enemy[loop2].spin-=steps[adjust];	// Spin Enemy Counter Clockwise
							}
						}
					}

					// Are Any Of The Enemies On Top Of The Player?
					if ((enemy[loop1].fx==player.fx) && (enemy[loop1].fy==player.fy))
					{
						lives--;								// If So, Player Loses A Life

						if (lives==0)							// Are We Out Of Lives?
						{
							gameover=TRUE;						// If So, gameover Becomes TRUE
						}

						ResetObjects();							// Reset Player / Enemy Positions
						PlaySound("../../Data/Die.wav", NULL, SND_SYNC);	// Play The Death Sound
					}
				}

				if (keys[VK_RIGHT] && (player.x<10) && (player.fx==player.x*60) && (player.fy==player.y*40))
				{
					hline[player.x][player.y]=TRUE;				// Mark The Current Horizontal Border As Filled
					player.x++;									// Move The Player Right
				}
				if (keys[VK_LEFT] && (player.x>0) && (player.fx==player.x*60) && (player.fy==player.y*40))
				{
					player.x--;									// Move The Player Left
					hline[player.x][player.y]=TRUE;				// Mark The Current Horizontal Border As Filled
				}
				if (keys[VK_DOWN] && (player.y<10) && (player.fx==player.x*60) && (player.fy==player.y*40))
				{
					vline[player.x][player.y]=TRUE;				// Mark The Current Verticle Border As Filled
					player.y++;									// Move The Player Down
				}
				if (keys[VK_UP] && (player.y>0) && (player.fx==player.x*60) && (player.fy==player.y*40))
				{
					player.y--;									// Move The Player Up
					vline[player.x][player.y]=TRUE;				// Mark The Current Verticle Border As Filled
				}

				if (player.fx<player.x*60)						// Is Fine Position On X Axis Lower Than Intended Position?
				{
					player.fx+=steps[adjust];					// If So, Increase The Fine X Position
				}
				if (player.fx>player.x*60)						// Is Fine Position On X Axis Greater Than Intended Position?
				{
					player.fx-=steps[adjust];					// If So, Decrease The Fine X Position
				}
				if (player.fy<player.y*40)						// Is Fine Position On Y Axis Lower Than Intended Position?
				{
					player.fy+=steps[adjust];					// If So, Increase The Fine Y Position
				}
				if (player.fy>player.y*40)						// Is Fine Position On Y Axis Lower Than Intended Position?
				{
					player.fy-=steps[adjust];					// If So, Decrease The Fine Y Position
				}
			}
			else												// Otherwise
			{
				if (keys[' '])									// If Spacebar Is Being Pressed
				{
					gameover=FALSE;								// gameover Becomes FALSE
					filled=TRUE;								// filled Becomes TRUE
					level=1;									// Starting Level Is Set Back To One
					level2=1;									// Displayed Level Is Also Set To One
					stage=0;									// Game Stage Is Set To Zero
					lives=5;									// Lives Is Set To Five
				}
			}

			if (filled)											// Is The Grid Filled In?
			{
				PlaySound("../../Data/Complete.wav", NULL, SND_SYNC);	// If So, Play The Level Complete Sound
				stage++;										// Increase The Stage
				if (stage>3)									// Is The Stage Higher Than 3?
				{
					stage=1;									// If So, Set The Stage To One
					level++;									// Increase The Level
					level2++;									// Increase The Displayed Level
					if (level>3)								// Is The Level Greater Than 3?
					{
						level=3;								// If So, Set The Level To 3
						lives++;								// Give The Player A Free Life
						if (lives>5)							// Does The Player Have More Than 5 Lives?
						{
							lives=5;							// If So, Set Lives To Five
						}
					}
				}

				ResetObjects();									// Reset Player / Enemy Positions

				for (loop1=0; loop1<11; loop1++)				// Loop Through The Grid X Coordinates
				{
					for (loop2=0; loop2<11; loop2++)			// Loop Through The Grid Y Coordinates
					{
						if (loop1<10)							// If X Coordinate Is Less Than 10
						{
							hline[loop1][loop2]=FALSE;			// Set The Current Horizontal Value To FALSE
						}
						if (loop2<10)							// If Y Coordinate Is Less Than 10
						{
							vline[loop1][loop2]=FALSE;			// Set The Current Vertical Value To FALSE
						}
					}
				}
			}

			// If The Player Hits The Hourglass While It's Being Displayed On The Screen
			if ((player.fx==hourglass.x*60) && (player.fy==hourglass.y*40) && (hourglass.fx==1))
			{
				// Play Freeze Enemy Sound
				PlaySound("Data/freeze.wav", NULL, SND_ASYNC | SND_LOOP);
				hourglass.fx=2;									// Set The hourglass fx Variable To Two
				hourglass.fy=0;									// Set The hourglass fy Variable To Zero
			}

			player.spin+=0.5f*steps[adjust];					// Spin The Player Clockwise
			if (player.spin>360.0f)								// Is The spin Value Greater Than 360?
			{
				player.spin-=360;								// If So, Subtract 360
			}

			hourglass.spin-=0.25f*steps[adjust];				// Spin The Hourglass Counter Clockwise
			if (hourglass.spin<0.0f)							// Is The spin Value Less Than 0?
			{
				hourglass.spin+=360.0f;							// If So, Add 360
			}

			hourglass.fy+=steps[adjust];						// Increase The hourglass fy Variable
			if ((hourglass.fx==0) && (hourglass.fy>6000/level))	// Is The hourglass fx Variable Equal To 0 And The fy
			{													// Variable Greater Than 6000 Divided By The Current Level?
				PlaySound("../../Data/hourglass.wav", NULL, SND_ASYNC);	// If So, Play The Hourglass Appears Sound
				hourglass.x=rand()%10+1;						// Give The Hourglass A Random X Value
				hourglass.y=rand()%11;							// Give The Hourglass A Random Y Value
				hourglass.fx=1;									// Set hourglass fx Variable To One (Hourglass Stage)
				hourglass.fy=0;									// Set hourglass fy Variable To Zero (Counter)
			}

			if ((hourglass.fx==1) && (hourglass.fy>6000/level))	// Is The hourglass fx Variable Equal To 1 And The fy
			{													// Variable Greater Than 6000 Divided By The Current Level?
				hourglass.fx=0;									// If So, Set fx To Zero (Hourglass Will Vanish)
				hourglass.fy=0;									// Set fy to Zero (Counter Is Reset)
			}

			if ((hourglass.fx==2) && (hourglass.fy>500+(500*level)))	// Is The hourglass fx Variable Equal To 2 And The fy
			{													// Variable Greater Than 500 Plus 500 Times The Current Level?
				PlaySound(NULL, NULL, 0);						// If So, Kill The Freeze Sound
				hourglass.fx=0;									// Set hourglass fx Variable To Zero
				hourglass.fy=0;									// Set hourglass fy Variable To Zero
			}

			delay++;											// Increase The Enemy Delay Counter
		}
	}

	// Shutdown
	KillGLWindow();												// Kill The Window
	return (msg.wParam);										// Exit The Program
}
