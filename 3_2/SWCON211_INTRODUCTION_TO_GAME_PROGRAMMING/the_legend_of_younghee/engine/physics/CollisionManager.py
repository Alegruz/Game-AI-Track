from engine.object.CollidableObject import CollidableObject


class CollisionManager:
    __slots__ = ["__collidables"]

    def __init__(self):
        self.__collidables: dict[str, CollidableObject] = dict()

    def add_collidable(self, key: str, collidable_object: CollidableObject) -> bool:
        assert isinstance(key, str) and issubclass(collidable_object.__class__, CollidableObject)

        if key in self.__collidables:
            return False

        self.__collidables[key] = collidable_object

    def contains_collidable_by_key(self, key: str):
        return key in self.__collidables

    def remove_collidable(self, key: str) -> bool:
        if key not in self.__collidables:
            return False

        del self.__collidables[key]

        return True

    def update(self, delta_time: float):
        for key in self.__collidables:
            for other_key in self.__collidables:
                if key is not other_key:
                    if self.__collidables[key].has_collided_with(other=self.__collidables[other_key]):
                        self.__collidables[key].on_collision_with(other=self.__collidables[other_key])
                        self.__collidables[other_key].on_collision_with(other=self.__collidables[key])
                        if key == "player":
                            print(f"{key} collided with {other_key}")
                        # print(f"\t{self.__collidables[key]._collision_box} ~ {self.__collidables[other_key]._collision_box}")