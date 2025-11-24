extends StaticBody3D

@onready var texto: Label3D = $Label3D

func _on_numero_episilon_area_entered(area: Area3D) -> void:
	texto.text = "ε"

func _on_numero_1_area_entered(area: Area3D) -> void:
	texto.text = "1"

func _on_numero_0_area_entered(area: Area3D) -> void:
	texto.text = "0"
