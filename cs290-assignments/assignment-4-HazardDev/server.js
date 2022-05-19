const fs   = require("fs");
const http = require("http");
const path = require("path");

const cache = {};
const public_dir = path.join(__dirname, "public");
const server = http.createServer((req, res) => {
	
	console.log(`Req Path: ${req.url}`);

	if(req.url == "/") req.url += "index.html";
	if(req.url.indexOf(".") == -1) req.url += ".html";

	if(req.url in cache) {

		console.info(`Serving from Mem: ${req.url}`);
		res.statusCode = req.url == "/404.html" ? 404 : 200;
		res.write(cache[req.url]);
		res.end();
		return;

	}

	fs.readFile(path.join(public_dir, req.url), (err, data) => {

		console.info(`Serving from File: ${req.url}`);

		if(err) {
			fs.readFile(path.join(public_dir, "404.html"), (err, data) => {
				if(err) {
					return;
				}
				res.statusCode = 404;
				cache[req.url] = data;				
				res.setHeader("Content-Type", "text/html");
				res.write(data);
				res.end();
			})
			return;
		}
		res.statusCode = 200;
		res.write(data);
		cache[req.url] = data;
		res.end();
	})

});

server.listen(process.env.PORT || 3000, () => {
	console.info("Server Started");
})