# Estado q2 de suma
extends State

func enter():
	pass

func physics_update(delta: float):
	if !parent.moving and !parent.pushing:
		var distancia = parent.sensor.get_collision_point().z
		#Beta
		if distancia < -0.1:
			pass
		#0
		if distancia <= 0.1 and distancia >= -0.1:
			pass
		#1
		if distancia > 0.1:
			print("1 -> Beta")
			parent.start_push_sequence(1.38, parent.pusher_empuje, 1.0)
			await get_tree().create_timer(4).timeout
			parent.move_to_global_position_smoothly(parent.global_position+Vector3(1,0,0), 0.5)
			transition_to("SumaQf")
