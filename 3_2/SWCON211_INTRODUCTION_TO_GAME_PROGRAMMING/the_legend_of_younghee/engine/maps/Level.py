class Level:
    def __init__(self):
        pass

    def __del__(self):
        print(f"i am being deleted!! {self}, {id(self)}")
