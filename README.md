# 3D-Raycast-Picking
### 0. Overview

1. click on the screen
2. emit a ray from the camera
3. select objects colliding with ray



### 1. Tutorial

[link](https://antongerdelan.net/opengl/raycasting.html)

### 2. Notice

- After you follow the tutorial, you will get a `glm::vec3 ray_world`. Now, you can calculate the intersection point between the ray and planes.

### 3. Known Issues

- Cannot select the objects closest to the camera. But you can easily implement it by yourself. To be specific, you need to calculate the distance between the camera and the hit point. Object with min distance would be selected.

