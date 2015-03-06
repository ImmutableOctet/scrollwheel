Strict

Public

' Preprocessor related:
#If TARGET = "glfw" And GLFW_VERSION = 3
	#SCROLLWHEEL_IMPLEMENTED = True
#End

#If Not SCROLLWHEEL_IMPLEMENTED
	#Error "Scroll-wheel functionality is currently unsupported on this target (~q${TARGET}~q)."
#End

' Imports (Monkey):
Import brl.gametarget

' Imports (Native):
Import "native/scrollwheel.${TARGET}.${LANG}"

' Functions (Monkey):
' Nothing so far.

' External bindings:
Extern

' Classes:
Class ScrollWheel Extends Null = "external_scrollwheel::scrollInfo"
	' Fields:
	Field XOffset:Float="xoffset"
	Field YOffset:Float="yoffset"
End

' Functions:
#If LANG = "cpp"
	Function GetScrollWheel:ScrollWheel()="external_scrollwheel::initWheel"
	
	#If BRL_GAMETARGET_IMPLEMENTED
		Function GetScrollWheel:ScrollWheel(Game:BBGame)="external_scrollwheel::initWheel"
	#End
#Else
	Function GetScrollWheel:ScrollWheel()="external_scrollwheel.initWheel"
	
	#If BRL_GAMETARGET_IMPLEMENTED
		Function GetScrollWheel:ScrollWheel(Game:BBGame)="external_scrollwheel.initWheel"
	#End
#End

Public