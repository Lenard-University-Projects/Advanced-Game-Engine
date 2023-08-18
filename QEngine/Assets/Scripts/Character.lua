require("class")

ScriptComponent = class()

rotationSpeed = 0.6

function ScriptComponent:Awake(this)
	print("Awake Character Method")
end

function ScriptComponent:Update(this)
	angle = QEngine.InputManager.GetAxis("Xaxis") * rotationSpeed
	this:GetTransform():RotateAboutY(angle)
	
	if QEngine.InputManager.GetKey("Forward") then
		print("Forward")
	end
	
	if QEngine.InputManager.GetKey("Backwards") then
		print("Backwards")
   	end
	
	if QEngine.InputManager.GetKey("Left") then
		print("Left")
	end
	
   	if QEngine.InputManager.GetKey("Right") then
		print("Right")
	end	
end

function ScriptComponent:OnCollisionEnter(this, collider)
	print("Collision Enter"..collider.GetName())
end

function ScriptComponent:OnCollisionExit(this, collider)
	print("Collision Exit"..collider.GetName())
end

