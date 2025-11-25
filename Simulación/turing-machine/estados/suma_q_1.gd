# Estado q1 de suma
extends State

func enter():
	pass

func physics_update(delta: float):
	if !parent.moving and !parent.pushing:
		var distancia = parent.sensor.get_collision_point().z
		#Beta
		if distancia < -0.1:
			parent.move_to_global_position_smoothly(parent.global_position+Vector3(-1,0,0), 0.5)
			transition_to("SumaQ2")
		#0
		elif distancia <= 0.1 and distancia >= -0.1:
			pass
		#1
		elif distancia > 0.1:
			parent.move_to_global_position_smoothly(parent.global_position+Vector3(1,0,0), 0.5)
