

function makeBoard(n) {
	let board = document.getElementById('board');
	board.dimensions = n;
	board.whiteTurn = true;
	board.ghostX = -1;
	board.ghostY = -1;
	board.tiles = [];
	for (var y = 0; y < n; y++) {
		let currentRow = [];
		for (var x = 0; x < n; x++) {
			currentRow.push(0);
		}
		board.tiles.push(currentRow);
	}
	while (board.hasChildNodes()) {
		board.removeChild(board.lastChild);
	}
	for (var y = 0; y < n - 1; y++) {
		let row = document.createElement('div');
		row.classList.add('row');
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
	placeTile(0, 0, true, false);
	placeTile(10, 5, false, false);
	placeTile(10, 6, false, false);
	placeTile(10, 7, false, false);
	placeTile(11, 6, false, false);
	placeTile(9, 6, false, false);
}

function eventInsideBoard(event, board) {
	let rect = board.getBoundingClientRect();
	if (event.x >= rect.left && event.x <= rect.right
		&& event.y >= rect.top && event.y <= rect.bottom) {
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
	if (!mouseHover) {
		board.tiles[y][x] = is_white ? 1 : 2;
		board.whiteTurn = !board.whiteTurn;
	}
	else {
		board.ghostX = x;
		board.ghostY = y;
	}
	let imgSrc = is_white ? 'white.png' : 'black.png';
	let imgParent = document.createElement('div');
	imgParent.classList.add('tile-parent');
	if (mouseHover)
		imgParent.id = 'ghost-tile';
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
	board.insertBefore(imgParent, board.childNodes[0]);
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

function onClickEvent(event) {
	event.preventDefault();
	removeGhostTile();
	let coords = mouseXYToBoardXY(event.y, event.x);
	let y = coords[0];
	let x = coords[1];
	if (board.tiles[y][x] == 0)
		placeTile(y, x, board.whiteTurn, false);
}

function onMouseMoveEvent(event) {
	event.preventDefault();
	let board = document.getElementById('board');
	let coords = mouseXYToBoardXY(event.y, event.x);
	let y = coords[0];
	let x = coords[1];
	if (board.tiles[y][x] == 0 && (board.ghostX != x || board.ghostY != y))
		placeTile(y, x, board.whiteTurn, true);
}