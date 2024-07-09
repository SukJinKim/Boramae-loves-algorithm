#include <iostream>
#include <cstring>

using namespace std;

const int MAX_N = 12;
const int MAX_M = 10;
const int INF = 987654321;

int cache[MAX_M][(1 << MAX_N)];

int n, k, m, l;

// preCourses[i] = i번째 과목의 선수과목 집합 (비트마스크로 표현)
int preCourses[MAX_N];
// curriculumns[i] = i번째 학기의 개설 강의 정보 집합 (비트마스크로 표현)
int courses[MAX_M];

int getPreCourseSet(int subset)
{
    int preCourseSet = 0; // subset에 대한 선수 과목 집합(비트마스크로 표현)

    // 최하위 비트를 추출하여 subset에 대한 선수 과목 집합 생성
    while (subset)
    {
        int aCourse = __builtin_ctz(subset);
        preCourseSet |= preCourses[aCourse];
        subset &= (subset - 1);
    }

    return preCourseSet;
}

// 현재 semester 학기이고 누적 수강 현황이 taken일 때,
// 졸업요건을 충족하기 위해 몇 학기가 더 필요한가
int graduate(int semester, int taken)
{
    // 졸업 요건(k개 이상 과목 수강)을 충족한 경우
    if (__builtin_popcount(taken) >= k)
        return 0;
    // m 학기를 지난 경우
    if (semester == m)
        return INF;

    int &ret = cache[semester][taken];
    if (ret != -1)
        return ret;

    ret = INF;
    int courseSet = courses[semester];
    for (int subset = courseSet; subset; subset = ((subset - 1) & courseSet))
    {
        // 학기당 최대 수강과목 수를 초과한 경우
        if (__builtin_popcount(subset) > l)
            continue;

        int preCourseSet = getPreCourseSet(subset);
        // 선수과목을 수강하지 않은 경우
        if ((taken & preCourseSet) != preCourseSet)
            continue;

        int nextTaken = taken | subset;
        ret = min(ret, graduate(semester + 1, nextTaken) + 1);
    }
    // 이번 학기 아무것도 듣지 않는 경우
    ret = min(ret, graduate(semester + 1, taken));

    return ret;
}

int main()
{
    int c;
    cin >> c;

    while (c--)
    {
        cin >> n >> k >> m >> l;

        // 선수과목 정보 저장
        for (int i = 0; i < n; ++i)
        {
            int num;
            cin >> num;

            int preCourseSet = 0, aPreCourse;
            for (int j = 0; j < num; ++j)
            {
                cin >> aPreCourse;
                preCourseSet |= (1 << aPreCourse);
            }
            preCourses[i] = preCourseSet;
        }
        // 학기별 개설 강의 정보 저장
        for (int i = 0; i < m; ++i)
        {
            int num;
            cin >> num;

            int courseSet = 0, aCourse;
            for (int j = 0; j < num; ++j)
            {
                cin >> aCourse;
                courseSet |= (1 << aCourse);
            }
            courses[i] = courseSet;
        }

        memset(cache, -1, sizeof(cache));

        int result = graduate(0, 0);
        if (result == INF)
            cout << "IMPOSSIBLE" << endl;
        else
            cout << result << endl;
    }

    return 0;
}