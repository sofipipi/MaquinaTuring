extends Node3D

@onready var caja = preload("res://cajinha.tscn");
@onready var originalPos = Vector3.ZERO

func _ready():
	for i in range(10):
		originalPos = Vector3(i, 0, 0)
		var instance = caja.instantiate()
		instance.position = originalPos
		find_child("Cinta").add_child(instance)
