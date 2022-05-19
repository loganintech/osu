import * as mysql from "mysql2";

function build(): any {
    const pool: mysql.Pool = mysql.createPool({
        host: "classmysql.engr.oregonstate.edu",
        port: 3306,
        database: "cs340_sasol",
        user: "cs340_sasol",
        password: "2492",
    });
    const promisePool = pool.promise();

    return promisePool
}

const conn = build()
export default conn;
