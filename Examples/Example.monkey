Strict

Public

' Preprocessor related:
#GLFW_WINDOW_TITLE = "Scroll-Wheel Test"
#GLFW_WINDOW_WIDTH = 256
#GLFW_WINDOW_HEIGHT = 128

' Imports:
Import mojo

Import scrollwheel

' Functions:
Function Main:Int()
	New Application()
	
	' Return the default response.
	Return 0
End

' Classes:
Class Application Extends App Final
	' Methods:
	Method OnCreate:Int()
		SetUpdateRate(30) ' 60
		
		Wheel = GetScrollWheel()
		
		#If CONFIG = "debug"
			If (Wheel = Null) Then
				DebugStop()
			Endif
		#End
		
		' Return the default response.
		Return 0
	End
	
	Method OnUpdate:Int()
		WheelString = "Wheel: " + Wheel.XOffset + ", " + Wheel.YOffset
		
		Print(WheelString)
		
		' Return the default response.
		Return 0
	End
	
	Method OnRender:Int()
		DrawText(WheelString, 4.0, 4.0)
		
		' Return the default response.
		Return 0
	End
	
	' Fields:
	Field Wheel:ScrollWheel
	Field WheelString:String
End