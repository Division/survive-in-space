//
//  Resources.h
//  Cpptest
//
//  Created by Nikita on 4/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>
#include <map>
#include "Utils.h"

class IResource {
public:
	virtual bool Load(const std::string& name) = 0;
};

class Mesh;
class Texture;
class Shader;
class Prefab;
class Scene;
class Font;

namespace resource {
	
	void Init(Scene *scene);
	
	Texture *GetTexture(const std::string& name);
	
	Shader *GetShader(const std::string& name);
	
	Prefab *GetPrefab(const std::string& name);
	
	Font *GetFont(const std::string& name);

	
	namespace manager {
	
		template <class T>
		class ResourceManager {
		public:
			
			T *GetResource(const std::string& name) {
				
				T *result = NULL;
				
				if (_resourceMap.count(name)) {
					result = _resourceMap[name].get();
				} else {
					ResourcePtr res(new T());
					if (res->Load(name)) {
						result = res.get();
						_resourceMap[name] = std::move(res);
					} else {
						utils::Log("Error loading resource: " + name);
					}
				}
				
				return result;
			}
			
		private:
			typedef std::unique_ptr<T> ResourcePtr;
			typedef std::map<std::string, ResourcePtr> ResourceMap;
			
			ResourceMap _resourceMap;
		};
		
		typedef ResourceManager<Texture> TextureManager;
		typedef ResourceManager<Shader> ShaderManager;
		typedef ResourceManager<Prefab> PrefabManager;
		typedef ResourceManager<Font> FontManager;
	}
	
}



#endif
