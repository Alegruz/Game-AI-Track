// The simplest situation is when ParamType is a reference type or a pointer type, but
// not a universal reference. In that case, type deduction works like this:
// 1. If expr’s type is a reference, ignore the reference part.
// 2. Then pattern-match expr’s type against ParamType to determine T.