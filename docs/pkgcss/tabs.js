function hideClick(name) {
  let v = document.getElementsByClassName(name);
  let i = 0;
  for (i = 0; i < v.length; i++) {
    v[i].style.display = 'none';
  }
  v = document.getElementsByClassName('li'+name);
  for (i=0;i<v.length;i++) {
      v[i].classList.remove('live');
    }
}

function showClick(name) {
  let v = document.getElementsByClassName(name);
  let i = 0;
  for (i = 0; i < v.length; i++) {
    v[i].style.display = 'initial';
    console.log(v[i].classList);
  }
  v = document.getElementsByClassName('li'+name);
  for (i=0;i<v.length;i++) {
      v[i].classList.add('live');
    }
}

function addli(ul, onclik, txt) {
  let li = document.createElement('li');
  let a = document.createElement('a');
  li.className = 'li'+txt;
  a.onclick = onclik;
  a.href = '#';
  a.textContent = txt;
  li.appendChild(a);
  ul.appendChild(li);
}

function onrun() {

  let tabs = document.getElementsByClassName("tabview");
  for (i = 0; i < tabs.length; i++) {
    let ul = document.createElement('ul');
    ul.className = "tabs";
    addli(ul, function(){hideClick('.net');hideClick('C++');showClick('node.js');return false;}, 'node.js');
    addli(ul, function(){hideClick('node.js');hideClick('C++');showClick('.net');return false;}, '.net');
    addli(ul, function(){hideClick('.net');hideClick('node.js');showClick('C++');return false;}, 'C++');
    tabs[i].insertBefore(ul,tabs[i].firstChild);
  }
  hideClick('node.js');
  hideClick('C++');
  showClick('.net');
}
