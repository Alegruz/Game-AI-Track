class ComponentType:
    RENDERABLE: int = 0
    CAPSULE: int = 1
    CHARACTER_MOVEMENT: int = 2


class Component:
    def __init__(self):
        pass

    def __del__(self):
        print(f"i am being deleted!! {self}, {id(self)}")
