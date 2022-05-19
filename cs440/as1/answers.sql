-- A
SELECT
  works.did,
  dname
FROM dept
LEFT JOIN works ON (dept.did = works.did)
LEFT JOIN emp ON (works.eid = emp.eid)
WHERE
  pct_time >= 50
GROUP BY
  dname

--  B
SELECT
  ename
FROM dept
LEFT JOIN works ON (works.did = dept.did)
LEFT JOIN emp ON (emp.eid = works.eid)
WHERE
  dept.did IN (3, 5, 8)
HAVING
  COUNT(dept.did) >= 3

--  C
SELECT
  dname
FROM dept
LEFT JOIN works ON (dept.did = works.did)
LEFT JOIN emp ON (works.eid = emp.eid)
WHERE
  emp.eid IS NULL

-- D
SELECT
  ename
FROM dept
LEFT JOIN works ON (dept.did = works.did)
LEFT JOIN emp ON (works.eid = emp.eid)
WHERE
  dept.did = 8

-- E
SELECT
  ename
FROM emp
WHERE
  salary = (
    SELECT
      MIN(salary)
    FROM emp
  )

-- F
SELECT
  *
FROM emp
LEFT JOIN works ON (works.eid = emp.eid)
LEFT JOIN dept ON (dept.did = works.did)
INNER JOIN (
    SELECT
      AVG(salary) AS "salary",
      dept.did
    FROM dept
    LEFT JOIN works ON (dept.did = works.did)
    LEFT JOIN emp ON (works.eid = emp.eid)
    WHERE
      salary IS NOT NULL
    GROUP BY
      dept.did
  ) AS avg_salaries
WHERE
  avg_salaries.salary >= emp.salary
  AND avg_salaries.did = dept.did
GROUP BY
  emp.eid

-- G
SELECT
  dname,
  AVG(emp.salary) AS "average"
FROM dept
LEFT JOIN works ON (works.did = dept.did)
LEFT JOIN emp ON (emp.eid = works.eid)
GROUP BY
  dept.did
HAVING
  COUNT(emp.eid) > 1