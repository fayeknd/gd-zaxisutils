# fayeknd's Z-Axis Utils
## A utility mod specifically for rendering 3D objects!
This mod is effectively a lightweight 3D Renderer taking advantage of the game's **OpenGL context**.
3D meshes can be displayed on a **zaxis::GDScene3D** node. the Scene3D is effectively a camera with a render texture attached.
Multiple Scene3Ds can exist, with their own nodes.

## GDMeshInstance3D and CCNode3D
**CCNode3D** is an extension of **CCNode** which adds several Z-Components. (Position, Rotation, Scale, Skew).
**GDMeshInstance3D** inherits a CCNode3D and can be placed inside a GDScene3D via **meshInstance->addToScene(scene)**.
It is important to note that **scene->addChild(meshInstance)** will not pass the scene pointer to the meshInstance, 
which is required.

Creating a generic Cube mesh inside a GDScene3D looks like this:
> auto scene = GDScene3D::create({320, 180});
> scene->setID("my-3d-scene"_spr);
> someHookedLayer->addChild(scene);

> auto cube = GDMeshInstance3D::create(ThreeDeeAPI_Cube);
> cube->setID("my-cube"_spr);
> cube->setPositionZ(-5); *// move the cube back slightly*
> cube->addToScene(scene);

> scene->m_camera.setRotationX(-35);
> scene->m_camera.setPositionY(3); *// camera looking down at cube*