

function getRessource(url, obj, cb) {
	ajax.get(url, { args: JSON.stringify(obj) }, cb);
}

function addSquareHelper(board, y, x) {
	let elt = document.createElement('div');
	elt.classList.add('square-helper');
	elt.style.marginLeft = (x * 52 - 4) + 'px';
	elt.style.marginTop = (y * 52 - 4) + 'px';
	board.appendChild(elt);
}

function makeBoard(n) {
	if (n < 5 || n > 19)
		return ;
	let board = document.getElementById('board');
	while (board.hasChildNodes()) {
		board.removeChild(board.lastChild);
	}
	if (n % 2 == 1)
		addSquareHelper(board, Math.floor(n / 2), Math.floor(n / 2));
	if (n >= 13) {
		addSquareHelper(board, 3, 3);
		addSquareHelper(board, 3, n - 4);
		addSquareHelper(board, n - 4, 3);
		addSquareHelper(board, n - 4, n - 4);
	}
	board.dimensions = n;
	board.whiteTurn = false;
	board.ghostX = -1;
	board.ghostY = -1;
	board.game_state = "playing";
	board.tiles = [];
	board.tilesElts = [];
	for (var y = 0; y < n; y++) {
		let currentRow = [];
		let currentRowElts = [];
		for (var x = 0; x < n; x++) {
			currentRow.push(0);
			currentRowElts.push(null);
		}
		board.tiles.push(currentRow);
		board.tilesElts.push(currentRowElts);
	}
	for (var y = 0; y < n - 1; y++) {
		let row = document.createElement('div');
		row.classList.add('gomoku-row');
		board.appendChild(row);
		for (var x = 0; x < n - 1; x++) {
			let _case = document.createElement('div');
			_case.classList.add('case');
			if (x < n - 2)
				_case.classList.add('no-border-right');
			if (y < n - 2)
				_case.classList.add('no-border-bottom');
			row.appendChild(_case);
		}
	}
}

function eventInsideBoard(event, board) {
	let rect = board.getBoundingClientRect();
	if (event.x > rect.left && event.x < rect.right
		&& event.y > rect.top && event.y < rect.bottom) {
		return true;
	}
	return false;
}

function removeGhostTile(event) {
	let board = document.getElementById('board');
	if (event && eventInsideBoard(event, board))
		return ;
	board.ghostX = -1;
	board.ghostY = -1;
	let tile = document.getElementById('ghost-tile');
	if (tile)
		tile.parentNode.removeChild(tile);
}

function placeTile(y, x, is_white, mouseHover) {
	removeGhostTile();
	let board = document.getElementById('board');
	if (!mouseHover)
		board.tiles[y][x] = is_white ? 2 : 1;
	else {
		board.ghostX = x;
		board.ghostY = y;
	}
	let imgSrc = is_white ? 'white.png' : 'black.png';
	let imgParent = document.createElement('div');
	imgParent.classList.add('tile-parent');
	if (mouseHover)
		imgParent.id = 'ghost-tile';
	else
		board.tilesElts[y][x] = imgParent;
	let x_decal = x * 52 - 24;
	imgParent.style.marginLeft = x_decal + 'px';
	let y_decal = y * 52 - 24;
	imgParent.style.marginTop = y_decal + 'px';
	let img = document.createElement('img');
	img.classList.add('tile');
	img.src = imgSrc;
	if (mouseHover)
		img.style.opacity = '0.5';
	imgParent.appendChild(img);
	let firstRow = 0;
	while (firstRow < board.childNodes.length &&
		!(board.childNodes[firstRow].classList.contains('gomoku-row'))) {
		firstRow++;
	}
	board.insertBefore(imgParent, board.childNodes[firstRow]);
}

function mouseXYToBoardXY(y, x) {
	let board = document.getElementById('board');
	let rect = board.getBoundingClientRect();
	x = x - rect.left;
	y = y - rect.top;
	x = x - 26;
	y = y - 26;
	x = Math.floor(x / 52);
	y = Math.floor(y / 52);
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= board.dimensions)
		x = board.dimensions - 1;
	if (y >= board.dimensions)
		y = board.dimensions - 1;
	return [y, x];
}

function updateBoard(board, tiles) {
	for (var y = 0; y < tiles.length; y++) {
		var line = "";
		for (var x = 0; x < tiles[y].length; x++) {
			line += (tiles[y][x] + " ");
			if (board.tiles[y][x] != tiles[y][x]) {
				if (tiles[y][x] === 0) {
					console.log("REMOVING")
					board.tilesElts[y][x].parentNode.removeChild(board.tilesElts[y][x]);
				}
				else if (board.tiles[y][x] === 0) {
					console.log("ici");
					placeTile(y, x, tiles[y][x] === 2 ? false : true, false);
				}
				else
					console.log("SHOULD NOT HAPPEN");
				board.tiles[y][x] = tiles[y][x];
			}
		}
		line += "     " + y;
		console.log(line);
	}
	console.log("s");
}

function onClickEvent(event) {
	let board = document.getElementById('board');
	if (board.game_state !== "playing")
		return ;
	if (aiTurn(board))
		return ;
	event.preventDefault();
	let coords = mouseXYToBoardXY(event.y, event.x);
	let y = coords[0];
	let x = coords[1];
	let req = {
		game_id: board.game_id,
		y: y,
		x: x
	};
	getRessource('/usermove', req, function(resp) {
		resp = JSON.parse(resp);
		if (!resp.ok)
			return alert('invalid move');
		board.game_state = resp.game_state;
		board.validNext = resp.valid_next;
		removeGhostTile();
		updateBoard(board, resp.tiles);
		//placeTile(y, x, board.whiteTurn, false);
		if (resp.game_state !== "playing")
			alert("final gamestate : " + resp.game_state);
		board.whiteTurn = !board.whiteTurn;
		console.log("changing turn");
		if (aiTurn(board)) {
			console.log("ICCIIII");
			makeAiTurn(board);
		}
	});
}

function aiTurn(board) {
	return (!board.whiteTurn && board.player1AI) || (board.whiteTurn && board.player2AI);
}

function onMouseMoveEvent(event) {
	event.preventDefault();
	let board = document.getElementById('board');
	if (board.game_state !== "playing")
		return ;
	let coords = mouseXYToBoardXY(event.y, event.x);
	let y = coords[0];
	let x = coords[1];
	let humanPlayer = !(aiTurn(board));
	if (humanPlayer && board.tiles[y][x] == 0 && (board.ghostX != x || board.ghostY != y))
		placeTile(y, x, board.whiteTurn, true);
}

function makeAiTurn(board) {
	if (board.game_state !== "playing")
		return ;
	let req = {
		game_id: board.game_id
	};
	getRessource('/makeaimove', req, function(resp) {
		let move = JSON.parse(resp);
		if (!move.ok)
			return console.log("invalid ai move");
		board.game_state = move.game_state;
		board.validNext = move.valid_next;
		updateBoard(board, move.tiles);
		//placeTile(move.y, move.x, board.whiteTurn, false);
		if (move.game_state !== "playing")
			alert("final gamestate : " + move.game_state);
		board.whiteTurn = !board.whiteTurn;
		if (aiTurn(board))
			makeAiTurn(board);
	})
}

function startGame() {
	let board = document.getElementById('board');
	let player1 = document.getElementById('player-type1');
	let player2 = document.getElementById('player-type2');
	board.player1AI = player1.checked;
	board.player2AI = player2.checked;
	let dimensions = Math.floor(document.getElementById('board-dimensions').value);
	let replace_existing = board.game_id ? true : false;
	let existing_id = board.game_id ? board.game_id : 0;
	let req = {
		dimensions: dimensions,
		replace_existing: replace_existing,
		existing_id: existing_id
	};
	getRessource('/makeboard', req, function(resp) {
		if (resp.startsWith("ok")) {
			let game_id = Math.floor(resp.substring(2, resp.length));
			board.game_id = game_id;
			makeBoard(dimensions);
			if (aiTurn(board))
				makeAiTurn(board);
		}
		else
			alert("error starting game");
	});
}