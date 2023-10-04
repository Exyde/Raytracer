# Questions
- What is inline ? Lives only in .h files ?
- Review cast, static_cast mainly.
- Research how to wait in .sh.
- Research how to pass argument to command line, specify executable name, and so on (more on g++)
- Virtual constructors , virtual methods ?

# Explore
- Add more Materials
- Add Lighting
- Add Camera Controls ? But nothing is realtime really here => Turn it Realtime ? Destroy my pc.
  - But it can also be a very low res realtime renderer.


# Notes

## Key Insights
- Focus. On. One. Thing. You'll learn 10 times faster
- Cult of done. Go through, end it. It's still a thing.
- Off internet help FOCUS a LOT ! Get your source, and isolate.
- **Dot Product** and **Cross Product** are really **CORE KNOWLEDGE** - Move this to Obsidian and build a shared mental map ?
- If you redo a project like this, comment everything more.
  - Also, ensure you understand deeply EVERYTHING you write. Like, you could explain it to someone.

## Diffuse Material (or Matte)
- Don't emit light
- Take the color of surrouding, but mix it with their own instrinsic color.
- Reflect light in a randomized direction
- Might absord aswell, which leads to darker material
- We'll first create a material that randomly diffuse light equally in all direction from surface

### Lambertian Reflection
- Evenly scattered rays on the hemisphere surface is nice : it give a soft diffuse model. But there's better.

- The distribution is based on *cos($theta$)*
  - It's the angle between the reflected ray and the surface normal.
  - Reflected ray is more likely to reflect in a direction near the surface normal.


### Linear and Gamme Color Space
- Most program assume that an image is *Gamma Corrected* before beeing written to a file.
- This means values in [0,1] have some transformation applied before beeing stored as bytes.
- Untransformed images are in *Linear Space*, whereas transformed one are in *Gamma Space*
- We'll use a simple version : gamma2.
  - from Gamma to Linear : we use power of 2 on our transform
  - from Linear to Gamma : 1/gamma, in our case just the square-root.

### Metallic
- Reflected Metal Ray : v + 2b from the hit point, v beeing the incoming vec

### Dielectrics
- Water, glass, diamond... Thing with transparency, I guess
- Light splits in **refracted** and **reflected**
  - We'll randomly choose what happens to an incoming ray
- **Snell's Law**
  - Honnestly too much math here for now, get back later (**TODO**)