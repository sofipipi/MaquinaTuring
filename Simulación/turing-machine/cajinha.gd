extends StaticBody3D

@onready var texto: Label3D = $Label3D
@onready var dato: RigidBody3D = $Dato

func _on_numero_episilon_area_entered(area: Area3D) -> void:
	texto.text = "β"

func _on_numero_1_area_entered(area: Area3D) -> void:
	texto.text = "1"

func _on_numero_0_area_entered(area: Area3D) -> void:
	texto.text = "0"

func get_dato() -> RigidBody3D:
	return dato
