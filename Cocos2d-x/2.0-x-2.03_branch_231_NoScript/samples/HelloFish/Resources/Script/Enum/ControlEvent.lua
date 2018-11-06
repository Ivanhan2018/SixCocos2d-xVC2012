--[[
----------------------------------
CCControlÊÂ¼þ
------------------------------------
Cool.Cat@2013-4-8 1:00:23
------------------------------------
]]

CCControlEvent={
		-- A touch-down event in the control.
    CCControlEventTouchDown           = 1,
    -- An event where a finger is dragged inside the bounds of the control.
    CCControlEventTouchDragInside     = 2,
    -- An event where a finger is dragged just outside the bounds of the control. 
    CCControlEventTouchDragOutside    = 4,
    -- An event where a finger is dragged into the bounds of the control.
    CCControlEventTouchDragEnter      = 8,
    -- An event where a finger is dragged from within a control to outside its bounds.
    CCControlEventTouchDragExit       = 16,
    -- A touch-up event in the control where the finger is inside the bounds of the control. 
    CCControlEventTouchUpInside       = 32,
    -- A touch-up event in the control where the finger is outside the bounds of the control.
    CCControlEventTouchUpOutside      = 64,
    -- A system event canceling the current touches for the control.
    CCControlEventTouchCancel         = 128,
    -- A touch dragging or otherwise manipulating a control, causing it to emit a series of different values.	
    CCControlEventValueChanged        = 512
}

