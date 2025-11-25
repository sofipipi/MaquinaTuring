extends Node3D

@onready var caja = preload("res://cajinha.tscn");
@onready var originalPos = Vector3.ZERO

const BETA = -0.25
const CERO = 0.0
const UNO = 0.25

var cinta = [ BETA, UNO, UNO, UNO, UNO, UNO, CERO, UNO, UNO, UNO, BETA]

func _ready():
	var i = -1
	for d in cinta:
		originalPos = Vector3(i, 0, 0)
		var instance: StaticBody3D = caja.instantiate()
		instance.position = originalPos
		find_child("Cinta").add_child(instance)
		var dato_instancia: RigidBody3D = instance.get_dato()
		dato_instancia.set_position(Vector3(0,0.5,d))
		i += 1
