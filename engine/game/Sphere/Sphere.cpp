//
//  Sphere.cpp
//  Cpptest
//
//  Created by Nikita on 5/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Sphere.h"
#include "Transform.h"
#include "Material.h"
#include "GameObject.h"

void Sphere::Awake() {

	triangles = Transform()->Find("SpawnTriangles");
	
	if (triangles) {
		triangles->GameObject()->SetActiveRecursively(false);
	}
	
	class Transform *geom = Transform()->Find("Geometry");
	if (geom) {
		sphereGeometry = geom->GameObject();
		
		Material material;
		material.Texture(resource::GetTexture("lightmap_brighter.pvr"));
		material.Shader(resource::GetShader("SimpleShader"));
		sphereGeometry->SetMaterial(material);
		physics::ConfigureAsCollisionGeometry(sphereGeometry, true, false);
	}

}