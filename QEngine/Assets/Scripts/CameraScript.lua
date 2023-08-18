require("class")

ScriptComponent = class()

zoomStep 	= 0.75
yawStep 	= 0.25
pitchStep 	= 0.25

function ScriptComponent:Awake(this)
	print("Awake Camera Method")
end

function ScriptComponent:Update(this)
    if QEngine.InputManager.GetKey("CameraZoomIn") then
		QEngine.Graphics.GetCamera():Zoom(-zoomStep)
	end
		if QEngine.InputManager.GetKey("CameraZoomOut") then
		QEngine.Graphics.GetCamera():Zoom(zoomStep)
   	end
	if QEngine.InputManager.GetKey("CameraYawLeft") then
		QEngine.Graphics.GetCamera():Yaw(yawStep)
	end
   	if QEngine.InputManager.GetKey("CameraYawRight") then
		QEngine.Graphics.GetCamera():Yaw(-yawStep)
	end
   	if QEngine.InputManager.GetKey("CameraPitchUp") then
		QEngine.Graphics.GetCamera():Pitch(-pitchStep)
   	end
	if QEngine.InputManager.GetKey("CameraPitchDown") then
		QEngine.Graphics.GetCamera():Pitch(pitchStep)
	end
end


