$('#submit').click(function () {
    alert('Just kidding! No registration skills yet!')
})

$('#run-mario-less').click(function () {
    height = getInt('#height')

    if (height < 0 || height > 8) {
        alert('height must be 1-8')
        return;
    }

    var s = '';
    for (var i = 1; i <= height; i++) {
        s += buildString(' ', height - i) + buildString('#', i) + '\n';
    }

    $('#output').val(s);
});

$('#run-mario-more').click(function () {
    height = getInt('#height')

    if (height < 0 || height > 8) {
        alert('height must be 1 - 8')
        return;
    }
    var s = '';
    for (var i = 1; i <= height; i++) {
        s += buildString(' ', height - i) + buildString('#', i) + '  ' + buildString('#', i) + '\n';
    }

    $('#output').val(s);
});

function getInt(tagID) {
    console.log('getInt called with: ' + tagID);
    var height = document.querySelector(tagID).value;
    console.log('return value from querySeletor: ' + height);
    return Number.parseInt(height);
}

function buildString(char, n) {

    var s = '';
    for (var i = 1; i <= n; i++) {
        s += char;
    }

    return s;
}