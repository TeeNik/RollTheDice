extends CharacterBody2D

@export var MovementSpeed : float = 100;

@onready var AnimationTree = $AnimationTree

func _physics_process(_delta):
	var InputDir = Vector2(
		Input.get_action_strength("Right") - Input.get_action_strength("Left"),
		Input.get_action_strength("Down") - Input.get_action_strength("Up"),
	)
	
	velocity = InputDir * MovementSpeed
	
	move_and_slide()
	
