class Math:
    @staticmethod
    def lerp_tuples(coord0: tuple[float, float], coord1: tuple[float, float], alpha: float) -> tuple[float, float]:
        return (1.0 - alpha) * coord0[0] + alpha * coord1[0], (1.0 - alpha) * coord0[1] + alpha * coord1[1]

    @staticmethod
    def lerp_float(x: float, y: float, alpha: float) -> float:
        return (1.0 - alpha) * x + alpha * y
