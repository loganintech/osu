import conn from "./db";
import express from "express";

const app = express();

app.get("/", async (req, res) => {
    try {
        const now = new Date();
        const time = `Accessed ${now.getMonth()}/${now.getDate()}/${now.getFullYear()} at ${now.getHours()}:${now.getMinutes() < 10 ? "0" + now.getMinutes() : now.getMinutes()}:${now.getSeconds()}.${now.getMilliseconds()}`;
        const data = await conn.query(`INSERT INTO diagnostic (text) VALUES ('${time}')`)
        // console.log(data);
    } catch (err) {
        console.error("Error occurred", err);
    }

    try {
        const data = await conn.query("SELECT * FROM diagnostic ORDER BY id DESC LIMIT 10");
        let arr: string[] = [];
        data[0].forEach((el: any) => {
            const { id, text } = el;
            // console.log(id, text);
            arr.push(text);
        });
        res.send(arr);
    } catch (err) {
        console.error("Error occurred", err);
    }
})

app.get("/delete", async (req, res) => {
    try {
        const data = await conn.query("DROP TABLE IF EXISTS diagnostic");
        // console.log(data);
    } catch (err) {
        console.error("Error occurred", err);
    }

    try {
        const data = await conn.query("CREATE TABLE diagnostic(id INT PRIMARY KEY AUTO_INCREMENT, text VARCHAR(255) NOT NULL)");
        // console.log(data);
    } catch (err) {
        console.error("Error occurred", err);
    }

    res.sendStatus(200);
})


try {
    app.listen(3000)
} catch (err) {
    console.error("Couldn't start the server.", err);
}

