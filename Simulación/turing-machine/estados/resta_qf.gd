# Estado qf de resta
extends State

func enter():
	pass

func physics_update(delta: float):
	if !parent.moving and !parent.pushing:
		var distancia = parent.sensor.get_collision_point().z
		#Beta
		if distancia < -0.1:
			pass
		elif distancia <= 0.1 and distancia >= -0.1:
			pass
		elif distancia > 0.1:
			pass
