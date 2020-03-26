# 문 제
`StudentRecord`에 대하여 멤버 길이 오프셋(offset) 테이블을 만들어라<br>
정수 자료형(`int`)의 크기는 4byte, 실수 자료형(`float`)의 크기는 4byte로 계산

```c++
typedef char String[9];

struct StudentRecord
{
	String firstName;
	String lastName;
	int id;
	float gpa;
	// char gender;
	int currentHours;
	int totalHours;
};
StudentRecord  student;
StudentRecords students[100];
```

| Variable | Length | Offset |
|-|:-:|:-:|
|`firstName`|9|0|
|`lastName`|18|9|
|`id`|4|20|
|`gpa`|4|24|
|`currentHours`|4|28|
|`totalHours`|4|32|