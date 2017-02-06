# A Simple Configuration Library

I wrote config as a part of a different project. I figured it would be a good idea to publish it separately since it was relatively generic. 

## Documentation
### Config files

There's an example configuration file in src/

Configuration files need to follow a few simple rules:

1. There will always be at least one [section]

2. The only character you cannot put in the name for a [section] is a closing square bracket (]) inside anywhere. This means [sect]ion] is not valid. Because I'm lazy, [sect[ion] is a valid name, but that's stupid and nobody would do that. 

3. It will never start with a key=value pair

4. You can have an equal sign in the second name of a key=value pair but not the first. ke=y=value is not valid, but key=val=ue is. This could be useful, but I can't think of how.

5. Each [section] must have at least one key=value pair

### Using the class

More to come (it's pretty straight forward. The example might be useful)

## Goals and TODO
- Add loading compatible text from a string (possibly useful for default configurations)
- Add single-file release for easy includes
- Get more sleep

