require("class")

ScriptComponent = class()

rotationSpeed = 0.1

function ScriptComponent:Update(this)
	angle = Merlin.InputManager.GetAxis("Xaxis") * rotationSpeed
	this:GetTransform():RotateAboutY(angle)
end


-- Exercise 9.7
function ScriptComponent:OnCollisionEnter(this, collider)
	print("Lua Collider Enter ".. collider:GetName())
end

-- Exercise 9.7
function ScriptComponent:OnCollisionExit(this, collider)
	print("Lua Collider Exit ".. collider:GetName())
end