function onClick() {
    let elementOffset = this.offsetTop;
    let tabsToHide = ["node.js", ".net", "C++"];
    tabsToHide.splice(tabsToHide.indexOf(this.text), 1);
    tabsToHide.forEach(hideTab);
    showTab(this.text);
    window.scrollBy(0, (this.offsetTop - elementOffset));
}

function hideTab(name) {
    let elementsToHide = document.getElementsByClassName(name);
    for (let i = 0; i < elementsToHide.length; i++) {
        elementsToHide[i].style.display = 'none';
    }
    elementsToHide = document.getElementsByClassName('li' + name);
    for (let i = 0; i < elementsToHide.length; i++) {
        elementsToHide[i].className = ('li' + name)
    }
}

function showTab(name) {
    let v = document.getElementsByClassName(name);
    for (let i = 0; i < v.length; i++) {
        v[i].style.marginLeft = "39.33px"
        v[i].style.marginTop = "-8px";
        v[i].style.display = 'inline-block';
        v[i].style.width = "575px";
        v[i].style.border = "ridge";
        v[i].style.borderColor = "silver";
        v[i].style.borderWidth = "7px";
    }
    v = document.getElementsByClassName('li' + name);
    for (i = 0; i < v.length; i++) {
        v[i].classList.add('live');
    }
}

function addli(ul, txt) {
    let li = document.createElement('li');
    let a = document.createElement('a');
    li.className = 'li' + txt;
    a.onclick = onClick;
    a.textContent = txt;
    li.appendChild(a);
    ul.appendChild(li);
}

function onrun() {
    let tabs = document.getElementsByClassName("tabview");
    for (let i = 0; i < tabs.length; i++) {
        let ul = document.createElement('ul');
        ul.className = "tabs";
        addli(ul, 'node.js');
        addli(ul, '.net');
        addli(ul, 'C++');
        tabs[i].insertBefore(ul, tabs[i].firstChild);
    }
    hideTab('node.js');
    hideTab('C++');
    showTab('.net');
}
