#!/usr/bin/node
const request = require('request');

const filmId = process.argv[2];
const url = `https://swapi-api.hbtn.io/api/films/${filmId}/`;

request(url, (error, response, body) => {
  if (error) {
    console.error(error);
    return;
  }

  const characters = JSON.parse(body).characters;
  printCharacter(characters, 0);
});

function printCharacter (characters, index) {
  if (index >= characters.length) {
    return;
  }

  request(characters[index], (error, response, body) => {
    if (error) {
      console.error(error);
      return;
    }

    console.log(JSON.parse(body).name);
    printCharacter(characters, index + 1);
  });
}
