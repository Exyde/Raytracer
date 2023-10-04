# Questions
- What is inline ? Lives only in .h files ?
- Review cast, static_cast mainly.
- Research how to wait in .sh.
- Research how to pass argument to command line, specify executable name, and so on (more on g++)
- Virtual constructors , virtual methods ?

# Notes

## Key Insights
- Focus. On. One. Thing. You'll learn 10 times faster
- Cult of done. Go through, end it. It's still a thing.
- Off internet help FOCUS a LOT ! Get your source, and isolate.
- **Dot Product** and **Cross Product** are really **CORE KNOWLEDGE** - Move this to Obsidian and build a shared mental map ?

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