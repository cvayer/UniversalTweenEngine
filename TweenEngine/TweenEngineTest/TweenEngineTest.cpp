// TweenEngine.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include "Tween/Easing.h"
#include "Tween/Manager.h"
#include "Tween/Tween.h"
#include "Tween/Timeline.h"
#include "Tween/TweenableValue.h"
#include "Tween/Path.h"
#include "cMyTweenListener.h"

//#include <windows.h>

#include "cQuad.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int running = GL_TRUE;
	// Initialize GLFW
	if( !glfwInit() )
	{
		return 0;
	}
	// Open an OpenGL window
	if( !glfwOpenWindow( 600,600, 0,0,0,0,0,0, GLFW_WINDOW ) )
	{
		glfwTerminate();
		return 0;
	}

	int mouseX, mouseY;

	glfwGetMousePos(&mouseX, &mouseY);

	float fDt = 1/30.0f;
	double time = glfwGetTime();

	float fDTFactor = 1.0f;

	Tween::Manager manager;

	float fHalfSize = 0.05f;

	Tween::Tween tweenX;
	Tween::Tween tweenY;
	Tween::Tween tweenRotation;
	Tween::TweenableFloat X;
	Tween::TweenableFloat Y;
	Tween::TweenableFloat Rotation;
	cMyTweenListener listener;


	tweenX.Setup(&X, Tween::InvalidType , 2.0f)->Ease(&(Tween::Easing::BOUNCE_OUT))->Target(-0.8f)->Repeat(Tween::Infinity, 0.5f, true)->Start(&manager);

	tweenY.Setup(&Y, Tween::InvalidType, 0.0f)->Ease(&(Tween::Easing::BOUNCE_OUT))->Target(0.5f)->Start(&manager);

	tweenRotation.Setup(&Rotation, Tween::InvalidType, 1.5f)->Ease(&(Tween::Easing::CUBIC_INOUT))->Target(360.0f)->Delay(0.5f)->Repeat(Tween::Infinity, 0.5f, true)->SetListener(&listener, 1, Tween::ITweenListener::eAll)->Start();


	cQuad quad1;
	cQuad quad2;
	cQuad quad3;

	quad1.m_fR = quad1.m_fB = 0.0f;
	quad2.m_fR = quad2.m_fG = 0.0f;
	quad3.m_fR = 0.0f;

	quad2.m_fX = quad2.m_fY = 0.5f;
	quad3.m_fX = quad3.m_fY = -0.5f;

	Tween::Tween tweenQuad1Position;
	tweenQuad1Position.Setup(&quad1, cQuad::eTweenPosition, 2.0f);
	tweenQuad1Position.Ease(&(Tween::Easing::QUAD_INOUT))->SetPath(&(Tween::Path::LINEAR))->Target(0.6f, -0.9f )->Waypoint(0.0f, -0.3f)->Waypoint(0.9f, -0.6f)->Repeat(-1, 0.5f, true)->Start(&manager);

	Tween::Tween tweenQuad1Color;
	tweenQuad1Color.Setup(&quad1, cQuad::eTweenColor, 0.5f);
	tweenQuad1Color.Ease(&(Tween::Easing::CIRC_INOUT))->Target(0.0f, 0.0f, 0.0f )->Repeat(-1, 0.0f, true)->Start(&manager);

	Tween::Timeline::CreateSequence()
		->Push(Tween::Tween::To(&quad3, cQuad::eTweenPosition, 1.0f)->Target(0.0f, 0.0f))
		->Push(Tween::Tween::To(&quad3, cQuad::eTweenRotation, 1.0f)->Target(360.0f)->Ease(&Tween::Easing::QUART_INOUT))
		->Push(Tween::Tween::To(&quad3, cQuad::eTweenPosition, 1.0f)->Target(-0.5f, -0.5f))
		->Push(Tween::Tween::To(&quad3, cQuad::eTweenSize, 1.0f)->Target(0.2f, true)->Ease(&Tween::Easing::BOUNCE_OUT))
		->Push(Tween::Tween::To(&quad3, cQuad::eTweenSize, 1.0f)->Target(-0.2f, true)->Ease(&Tween::Easing::QUART_INOUT))
		->PushPause(1.0f)
		->BeginParallel()
		->Push(Tween::Tween::To(&quad3, cQuad::eTweenRotation, 1.0f)->Target(360.0f, true)->Ease(&Tween::Easing::BOUNCE_OUT))
		->Push(Tween::Tween::To(&quad3, cQuad::eTweenPosition, 1.0f)->Target(0.0f, 0.0f))
		->End()
		->Repeat(-1, 0.2f)
		->Start(&manager,1);
		
	
	Tween::Tween::To(&quad2, cQuad::eTweenRotation, 1.0f)->Ease(&(Tween::Easing::ELASTIC_OUT))->Target(360.0f)->Repeat(4, 0.2f, true)->SetListener(&listener, 0, Tween::ITweenListener::eAll)->Start(&manager, 1);

	Tween::Tween::Call(&listener);

	float fGroup0DtFactor = 1.0f;
	float fGroup1DtFactor = 1.0f;

	float fGroupDtFactorIncrement = 0.1f;


	gluOrtho2D(-1.0, 1.0, -1.0f, 1.0);

	// Main loop
	while( running )
	{
		fDt = (float) (glfwGetTime() - time );
		fDt *= fDTFactor;
		time = glfwGetTime();

		if(glfwGetKey( GLFW_KEY_UP ))
		{
			fGroup0DtFactor += fGroupDtFactorIncrement;
			printf("DT 0 factor = %f\n", fGroup0DtFactor);
			manager.SetDtFactor(fGroup0DtFactor, 0);
		}

		if(glfwGetKey( GLFW_KEY_DOWN ))
		{
			fGroup0DtFactor -= fGroupDtFactorIncrement;
			printf("DT 0 factor = %f\n", fGroup0DtFactor);
			manager.SetDtFactor(fGroup0DtFactor, 0);
		}

		if(glfwGetKey( GLFW_KEY_RIGHT ))
		{
			fGroup1DtFactor += fGroupDtFactorIncrement;
			printf("DT 1 factor = %f\n", fGroup1DtFactor);
			manager.SetDtFactor(fGroup1DtFactor, 1);
		}

		if(glfwGetKey( GLFW_KEY_LEFT ))
		{
			fGroup1DtFactor -= fGroupDtFactorIncrement;
			printf("DT 1 factor = %f\n", fGroup1DtFactor);
			manager.SetDtFactor(fGroup1DtFactor, 1);
		}



	//	LARGE_INTEGER t1, t2;
		
	//	QueryPerformanceCounter(&t1);
		manager.Update(fDt);
	//	QueryPerformanceCounter(&t2);
	//	float sec = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
	/*	double managerUpdate = glfwGetTime() - time;
		printf("%f\n", sec);*/


		tweenRotation.Update(fDt);


		int NewMouseX, NewMouseY;
		glfwGetMousePos(&NewMouseX, &NewMouseY);

		if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			float xDelta = (NewMouseX - mouseX) / 100.0f;
		//	fDTFactor += xDelta;
		//	printf("DT factor = %f\n", fDTFactor);
		}
		mouseX = NewMouseX;




		// OpenGL rendering goes here...
		glClear( GL_COLOR_BUFFER_BIT );

		glLoadIdentity();
		
		glPushMatrix();
		glTranslatef(X, Y, 0.0f);
		glRotatef(Rotation, 0.0f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLE_STRIP);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f( - fHalfSize,  + fHalfSize);
		glVertex2f( + fHalfSize,  + fHalfSize);
		glVertex2f( - fHalfSize,  - fHalfSize);
		glVertex2f( + fHalfSize,  - fHalfSize);
		glEnd();
		glPopMatrix();

		
		quad1.Render();
		quad2.Render();
		quad3.Render();
		
		// Swap front and back rendering buffers
		glfwSwapBuffers();

		// Check if ESC key was pressed or window was closed
		running = !glfwGetKey( GLFW_KEY_ESC ) &&
			glfwGetWindowParam( GLFW_OPENED );
	}
	// Close window and terminate GLFW
	glfwTerminate();
	// Exit program
	return 1;
}
