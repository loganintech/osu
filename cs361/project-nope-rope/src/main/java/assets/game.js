var isSetup = true;
var placedShips = 0;
var sonarUsed = 0;
var game;
var shipType;
var vertical;
var submerged = false;

// for (int row = x - 2; row <= x + 2; row++) {
//     if (row <= 0 || row > this.rows) continue;

//     for (int col = charToColInt(y) - (2 - Math.abs(row - x)); col <= charToColInt(y) + (2 - Math.abs(row - x)); col++) {
//         if (col <= 0 || col > this.cols) continue;

function drawSonar(mouseEvent) {
    if (!document.getElementById("use_sonar").checked || isSetup) return;
    const grid = mouseEvent.toElement.parentNode.parentNode;
    const x = mouseEvent.toElement.cellIndex;
    const y = mouseEvent.toElement.parentElement.rowIndex;
    for (let row = x - 2; row <= x + 2; row++) {
        if (row < 0 || row >= 10) continue;

        for (let col = y - (2 - Math.abs(row - x)); col <= y + (2 - Math.abs(row - x)); col++) {
            if (col < 0 || col >= 10) continue;

            grid.childNodes[col].cells[row].classList.add("sonar-color");
        }
    }

}

function removeSonar(mouseEvent) {
    if (isSetup) return;

    const grid = mouseEvent.toElement.parentNode.parentNode;
    const x = mouseEvent.toElement.cellIndex;
    const y = mouseEvent.toElement.parentElement.rowIndex;
    for (let row = 0; row < 10; row++) {
        for (let col = 0; col < 10; col++) {
            grid.childNodes[col].cells[row].classList.remove("sonar-color");
        }
    }
}

function makeGrid(table, isPlayer) {
    for (let i = 0; i < 10; i++) {
        let row = document.createElement('tr');
        for (let j = 0; j < 10; j++) {
            let column = document.createElement('td');
            column.addEventListener("click", cellClick);
            column.addEventListener("mouseover", drawSonar);
            column.addEventListener("mouseout", removeSonar);
            row.appendChild(column);
        }
        table.appendChild(row);
    }
}

function markHits(board, elementId, surrenderText) {
    if (!board.attacks) return;
    board.attacks.forEach((attack) => {
        let className;
        if (attack.result === "MISS")
            className = "miss";
        else if (attack.result === "HIT")
            className = "hit";
        else if (attack.result === "SUNK")
            className = "hit";
        else if (attack.result === "SURRENDER"){

                var modal = document.getElementById(surrenderText);

                var span = document.getElementsByClassName("close")[0];
                modal.style.display = "block";
                span.onclick = function() {
                    modal.style.display = "none";
                }
                window.onclick = function(event) {
                    if (event.target == modal) {
                        modal.style.display = "none";
                    }
                }

        }
        document.getElementById(elementId).rows[attack.location.row - 1].cells[attack.location.column.charCodeAt(0) - 'A'.charCodeAt(0)].classList.add(className);
    });
}

function redrawGrid() {
    Array.from(document.getElementById("opponent").childNodes).forEach((row) => row.remove());
    Array.from(document.getElementById("player").childNodes).forEach((row) => row.remove());
    makeGrid(document.getElementById("opponent"), false);
    makeGrid(document.getElementById("player"), true);
    if (game === undefined) {
        return;
    }

    game.playersBoard.ships.forEach((ship) => ship.occupiedSquares.forEach((square) => {
        document.getElementById("player").rows[square.row - 1].cells[square.column.charCodeAt(0) - 'A'.charCodeAt(0)].classList.add("occupied");
    }));

    game.opponentsBoard.visibleSquares.forEach((square) => {
        if(square.type == "SHIP")
        {
            document.getElementById("opponent").rows[square.row - 1].cells[square.column.charCodeAt(0) - 'A'.charCodeAt(0)].classList.add("occupied");
        }
        else
        {
            document.getElementById("opponent").rows[square.row - 1].cells[square.column.charCodeAt(0) - 'A'.charCodeAt(0)].classList.add("sonar");
        }
    });

    markHits(game.opponentsBoard, "opponent", "winModal");
    markHits(game.playersBoard, "player", "surrModal");

    // front end captains quarters
    for (var i = 0; i < game.playersBoard.ships.length; i++) {
        for (var j = 0; j < game.playersBoard.ships[i].occupiedSquares.length; j++) {
            if (game.playersBoard.ships[i].occupiedSquares[j].captains == true) {
                document.getElementById("player").rows[game.playersBoard.ships[i].occupiedSquares[j].row - 1].cells[game.playersBoard.ships[i].occupiedSquares[j].column.charCodeAt(0) - 'A'.charCodeAt(0)].classList.add("captains");
            }
        }
    }
}

var oldListener;
function registerCellListener(f) {
    let el = document.getElementById("player");
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            let cell = el.rows[i].cells[j];
            cell.removeEventListener("mouseover", oldListener);
            cell.removeEventListener("mouseout", oldListener);
            cell.addEventListener("mouseover", f);
            cell.addEventListener("mouseout", f);
        }
    }
    oldListener = f;
}

function cellClick() {
    let row = this.parentNode.rowIndex + 1;
    let col = String.fromCharCode(this.cellIndex + 65);
    console.log(col);
    if (isSetup) {
        sendXhr("POST", "/place", { game: game, shipType: shipType, x: row, y: col, isVertical: vertical, isSubmerged: submerged }, function (data) {

            game = data;

            redrawGrid();
            placedShips++;
            switch (shipType) {
                case "MINESWEEPER":
                    document.getElementById('smallBoatImage').src = "/assets/images/smallBoatPlaced.png"
                    break;
                case "DESTROYER":
                    document.getElementById('medBoatImage').src = "/assets/images/medBoatPlaced.png"
                    break;
                case "BATTLESHIP":
                    document.getElementById('bigBoatImage').src = "/assets/images/bigBoatPlaced.png"
                    break;
                case "SUBMARINE":
                    document.getElementById("submarineImage").src = "/assets/images/submarinePlaced.png"
                    break;
            }
            if (placedShips == 4) {
                isSetup = false;
                registerCellListener((e) => { });
            }

        });
    } else if (document.getElementById("use_sonar").checked) {

        sonarUsed++;
        if(sonarUsed <= 2)
        {
            sendXhr("POST", "/sonar", { game: game,  x: row, y: col}, function (data) {
                game = data;
                redrawGrid();
            })
        }
        else
        {
            var modal = document.getElementById('errModal');
            var span = document.getElementsByClassName("close")[0];
            modal.style.display = "block";
            span.onclick = function () {
                modal.style.display = "none";
            }
            window.onclick = function (event) {
                if (event.target == modal) {
                    modal.style.display = "none";
                }
            }
        }
    }
    else {

        sendXhr("POST", "/attack", { game: game, x: row, y: col }, function (data) {
            game = data;
            redrawGrid();
        })
    }
}

function sendXhr(method, url, data, handler) {
    var req = new XMLHttpRequest();
    req.addEventListener("load", function (event) {
        if (req.status != 200) {
            // Get the modal
            var modal = document.getElementById('errModal');
            var span = document.getElementsByClassName("close")[0];
            modal.style.display = "block";
            span.onclick = function () {
                modal.style.display = "none";
            }
            window.onclick = function (event) {
                if (event.target == modal) {
                    modal.style.display = "none";
                }
            }
            return;
        }
        handler(JSON.parse(req.responseText));
    });
    req.open(method, url);
    req.setRequestHeader("Content-Type", "application/json");
    req.send(JSON.stringify(data));
}

function place(size) {
    return function () {
        let row = this.parentNode.rowIndex;
        let col = this.cellIndex;
        vertical = document.getElementById("is_vertical").checked;
        submerged = document.getElementById("is_submerged").checked;

        let table = document.getElementById("player");
        for (let i = 0; i < size; i++) {
            let cell;
            if (vertical) {
                let tableRow = table.rows[row + i];
                if (tableRow === undefined) {
                    // ship is over the edge; let the back end deal with it
                    break;
                }
                cell = tableRow.cells[col];
            } else {
                cell = table.rows[row].cells[col + i];
            }
            if (cell === undefined) {
                // ship is over the edge; let the back end deal with it
                break;
            }
            cell.classList.toggle("placed");
        }
    }
}

function initGame() {
    makeGrid(document.getElementById("opponent"), false);
    makeGrid(document.getElementById("player"), true);
    document.getElementById("place_minesweeper").addEventListener("click", function (e) {
        shipType = "MINESWEEPER";
        registerCellListener(place(2));
    });
    document.getElementById("place_destroyer").addEventListener("click", function (e) {
        shipType = "DESTROYER";
        registerCellListener(place(3));
    });
    document.getElementById("place_battleship").addEventListener("click", function (e) {
        shipType = "BATTLESHIP";
        registerCellListener(place(4));
    });
    document.getElementById("place_submarine").addEventListener("click", function (e) {
        shipType = "SUBMARINE"
        registerCellListener(place(5));
    })
    sendXhr("GET", "/game", {}, function (data) {
        game = data;
    });
};
