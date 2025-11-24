extends CharacterBody3D

@export var speed: float = 5.0
@export var sprint_multiplier: float = 1.8
@export var acceleration: float = 10.0
@export var deacceleration: float = 10.0
@export var gravity: float = ProjectSettings.get_setting("physics/3d/default_gravity")
@export var jump_velocity: float = 4.5
@export var mouse_sensitivity: float = 0.12

@export var push_force: float = 1
@export var max_velocity: float = 0.1

@onready var pivot: Node3D = $Pivot
@onready var camera: Camera3D = $Pivot/Camera3D

func _ready() -> void:
	# Capture the mouse for mouse-look. Press ESC to release (see _unhandled_input).
	Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)

func _unhandled_input(event: InputEvent) -> void:
	if event is InputEventMouseMotion:
		# Yaw (rotate the body)
		rotate_y(-deg_to_rad(event.relative.x * mouse_sensitivity))
		# Pitch (rotate the pivot)
		var new_pitch: float = pivot.rotation_degrees.x - event.relative.y * mouse_sensitivity
		new_pitch = clamp(new_pitch, -89.0, 89.0)
		pivot.rotation_degrees.x = new_pitch

	if event is InputEventKey and event.pressed and event.is_action("scape"):
		Input.set_mouse_mode(Input.MOUSE_MODE_VISIBLE)

func _physics_process(delta: float) -> void:
	# Read input as a 2D vector (x = right, y = forward)
	var input_vec := Vector2(
		Input.get_action_strength("D") - Input.get_action_strength("A"),
		Input.get_action_strength("W") - Input.get_action_strength("S")
	)
	if input_vec.length() > 1.0:
		input_vec = input_vec.normalized()

	# Build target velocity in world space based on the player's orientation
	var forward_dir: Vector3 = -transform.basis.z
	var right_dir: Vector3 = transform.basis.x
	var target_velocity: Vector3 = (forward_dir * input_vec.y + right_dir * input_vec.x) * speed

	# Sprint
	if Input.is_action_pressed("sprint"):
		target_velocity *= sprint_multiplier

	# Smoothly interpolate horizontal velocity (x/z)
	velocity.x = lerp(velocity.x, target_velocity.x, acceleration * delta) if target_velocity.length() > 0.01 else lerp(velocity.x, 0.0, deacceleration * delta)
	velocity.z = lerp(velocity.z, target_velocity.z, acceleration * delta) if target_velocity.length() > 0.01 else lerp(velocity.z, 0.0, deacceleration * delta)

	# Gravity & jumping
	if is_on_floor():
		# Reset downward velocity when grounded
		if Input.is_action_just_pressed("salto"):
			velocity.y = jump_velocity
		else:
			# keep a tiny downward snap to stay on slopes if needed
			velocity.y = -0.01
	else:
		velocity.y -= gravity * delta

	for i in get_slide_collision_count():
		var collision = get_slide_collision(i)
		var collision_crate = collision.get_collider()
		if collision_crate.is_in_group("pushable_group") and abs(collision_crate.get_linear_velocity().z) < max_velocity:
			collision_crate.apply_central_impulse(collision.get_normal() * -push_force)
		
	# Move and slide using up as floor normal
	move_and_slide()
