extends Node3D

@export var push_force: float = 0.1
@export var max_velocity: float = 0.01
@onready var pusher_empuje = $Carrito1/Pusher as CharacterBody3D
@onready var pusher_devolver = $Carrito2/Pusher as CharacterBody3D
@onready var sensor: RayCast3D = $Carrito1/RayCast3D

@export var moving = false
@export var pushing = false

# Constantes importantes
const DEFAULT_SCALE_Z = 1.0       # Escala por defecto en el eje Z
const PUSH_DURATION = 0.5
const RETURN_DURATION = 1.0

# Almacena la posición inicial y la escala inicial para el retorno
var initial_position: Vector3
var initial_scale: Vector3

func _ready() -> void:
	#Beta
	#start_push_sequence(1.60, pusher_empuje, 1.0)
	#1
	#start_push_sequence(1.40, pusher_devolver, -1.0)
	#0
	#start_push_sequence(1.12, pusher_empuje, 1.0)
	pass

func _physics_process(delta: float) -> void:
	for i in pusher_empuje.get_slide_collision_count():
		var collision = pusher_empuje.get_slide_collision(i)
		var collision_crate = collision.get_collider()
		if collision_crate.is_in_group("pushable_group") and abs(collision_crate.get_linear_velocity().z) < max_velocity:
			collision_crate.apply_central_impulse(collision.get_normal() * -push_force)

#Movimiento
func move_to_global_position_smoothly(target_global_position: Vector3, duration: float):
	if (target_global_position.x == -1):
		print("Izquiera")
	else:
		print("Derecha")
	moving = true
	# El Tween moverá el nodo desde su posición actual hasta la posición objetivo 
	var tween = create_tween()
	tween.tween_property(
		self, # El nodo al que aplicamos la propiedad (self = este script)
		"global_position", # La propiedad que queremos animar
		target_global_position, # El valor objetivo
		duration # El tiempo que dura la animación
	)\
	.set_trans(Tween.TRANS_SINE)\
	.set_ease(Tween.EASE_IN_OUT)

	# Opcional: Conectar una señal para saber cuándo terminó el movimiento
	tween.finished.connect(_on_move_finished)
	

func _on_move_finished():
	moving = false

#Movimiento de pushers
func start_push_sequence(distance: float, pusher: CharacterBody3D, direction: float):
	pushing = true
	initial_position = pusher.position
	initial_scale = pusher.scale
	var tween_extend = create_tween()
	# === VALORES OBJETIVO ===
	
	# 1. Escala Final: La escala Z se aumenta por la distancia de empuje.
	var final_scale = initial_scale
	final_scale.z = DEFAULT_SCALE_Z + distance
	
	# 2. Posición Final: Compensación.
	# El cilindro se mueve la mitad de la distancia de empuje en la dirección opuesta al empuje.
	# El factor -1 es para que el movimiento sea opuesto a la dirección de empuje.
	var final_position = initial_position + Vector3(0,0,direction) * (-distance / 2.0) 
	
	
	# 1. EMPUJAR/EXTENDER (Escala y Posición al mismo tiempo)
	
	# Animación de ESCALA
	tween_extend.tween_property(pusher, "scale", final_scale, PUSH_DURATION)\
		.set_trans(Tween.TRANS_QUART)\
		.set_ease(Tween.EASE_OUT)
		
	# Animación de POSICIÓN (Compensación)
	tween_extend.tween_property(pusher, "position", final_position, PUSH_DURATION)\
		.set_trans(Tween.TRANS_QUART)\
		.set_ease(Tween.EASE_OUT)

	# 2. Esperar
	tween_extend.pause()
	await get_tree().create_timer(0.5).timeout
	tween_extend.play()

	# 3. DEVOLVER/RETORNAR (Escala y Posición al mismo tiempo)
	
	# Animación de ESCALA al valor inicial (initial_scale)
	tween_extend.tween_property(pusher, "scale", initial_scale, RETURN_DURATION)\
		.set_trans(Tween.TRANS_SINE)\
		.set_ease(Tween.EASE_IN_OUT)
		
	# Animación de POSICIÓN al valor inicial (initial_position)
	tween_extend.tween_property(pusher, "position", initial_position, RETURN_DURATION)\
		.set_trans(Tween.TRANS_SINE)\
		.set_ease(Tween.EASE_IN_OUT)
		
	tween_extend.finished.connect(_on_push_finished)

func _on_push_finished():
	pushing = false
