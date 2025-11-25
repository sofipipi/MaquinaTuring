# State.gd
class_name State
extends Node

# Referencia a la máquina de estados que contiene este estado.
# Esto permite que el estado le pida a la máquina que haga una transición.
var state_machine: Node = null 
# Referencia al personaje (por ejemplo, el Player o Enemy)
var parent: Node3D = null
# --- Métodos de ciclo de vida del estado ---

# Llamado al entrar al estado. Útil para inicializar animaciones o variables.
func enter():
	pass

# Llamado en cada frame (similar a _process). Para la lógica constante del estado.
func update(delta: float):
	pass
	
# Llamado para la lógica de física (similar a _physics_process).
func physics_update(delta: float):
	pass
	
# Llamado al salir del estado. Útil para limpiar o detener animaciones.
func exit():
	pass

# Llama a la máquina de estados para cambiar a un nuevo estado.
func transition_to(new_state_name: String):
	# Asegúrate de que la máquina de estados existe y tiene el método transition_to
	if state_machine:
		state_machine.transition_to(new_state_name)
