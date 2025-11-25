# StateMachine.gd
extends Node

# Estado actual. Se inicializa en _ready.
var current_state: State = null
# Diccionario para almacenar todos los estados hijos.
var states: Dictionary = {}

# El nodo que la FSM controla (Player, Enemy, etc.)
@export var parent_node: Node3D = null 

func _ready():
	# 1. Recoger todos los nodos hijos (que son tus scripts de estado)
	for child in get_children():
		if child is State:
			var state = child as State
			states[state.name] = state # Almacena el estado por su nombre
			state.state_machine = self # Dale al estado una referencia a esta FSM
			state.parent = parent_node # Dale al estado una referencia al nodo principal
	
	# 2. Inicializar con el primer estado
	if states.size() > 0:
		current_state = states[find_child(Global.tipo_automata).name]
		current_state.enter()

func _process(delta: float):
	if current_state:
		current_state.update(delta)

func _physics_process(delta: float):
	if current_state:
		current_state.physics_update(delta)

# --- Método clave de la Máquina de Estados ---
func transition_to(new_state_name: String):
	print(new_state_name)
	# 1. Verifica si el nuevo estado existe
	if states.has(new_state_name) and states[new_state_name] != current_state:
		
		# 2. Llama al método de salida del estado actual
		if current_state:
			current_state.exit()
			
		# 3. Cambia al nuevo estado
		current_state = states[new_state_name]
		
		# 4. Llama al método de entrada del nuevo estado
		current_state.enter()
