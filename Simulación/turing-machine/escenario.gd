extends Node3D

@onready var caja = preload("res://cajinha.tscn");
@onready var controlador = preload("res://controlador_carritos.tscn")
@onready var originalPos = Vector3.ZERO
@onready var texto_automata = $CambioAutomata/Label3D
@onready var controlador_instancia: Node3D

const BETA = -0.25
const CERO = 0.0
const UNO = 0.25

var cinta = [ BETA, UNO, UNO, UNO, CERO, UNO, UNO, UNO, BETA]

func _ready():
	texto_automata.text = "Suma"
	generar_maquina(cinta)


func generar_maquina(cinta: Array):
	controlador_instancia = controlador.instantiate()
	add_child(controlador_instancia)
	controlador_instancia.set_position(Vector3(-5,0,0))
	var i = -1
	for d in cinta:
		originalPos = Vector3(i, 0, 0)
		var instance = caja.instantiate()
		instance.position = originalPos
		find_child("Cinta").add_child(instance)
		var dato_instancia: RigidBody3D = instance.get_dato()
		dato_instancia.set_position(Vector3(0,0.5,d))
		i += 1



func _on_cambio_automata_area_entered(area: Area3D) -> void:
	if Global.tipo_automata == "SumaQ0":
		Global.tipo_automata = "RestaQ0"
		texto_automata.text = "Resta"
	else: 
		Global.tipo_automata = "SumaQ0"
		texto_automata.text = "Suma"



func _on_generar_automata_area_entered(area: Area3D) -> void:
	#generar_maquina(cinta)
	if find_child("Cinta").get_child_count() > 0:
		for child in find_child("Cinta").get_children():
			child.queue_free()
	controlador_instancia.cleanup_and_free()
	generar_maquina(cinta)
	
