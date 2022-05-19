/*
 * Write your JS code in this file.
 */


//#region Globally Required
const postsParent = document.getElementById("posts");

function postTitle(element) {
	return element.getElementsByClassName("post-title")[0].text;
}
//#endregion


//#region Filters

//#region Condition Filter getElements
const updateButton    = document.getElementById("filter-update-button");
const newFilter       = document.getElementById("filter-condition-new");
const excellentFilter = document.getElementById("filter-condition-excellent");
const goodFilter      = document.getElementById("filter-condition-good");
const fairFilter      = document.getElementById("filter-condition-fair");
const poorFilter      = document.getElementById("filter-condition-poor");
//#endregion

//#region Text Price City filters
const cityFilter      = document.getElementById("filter-city");
const minPriceFilter  = document.getElementById("filter-min-price");
const maxPriceFilter  = document.getElementById("filter-max-price");
const textFilter      = document.getElementById("filter-text");
//#endregion


//#region Remove and Add to DOM
let allItems = [];

for(let i = 0; i < postsParent.children.length; i++) {
	allItems.push(postsParent.children[i].getElementsByClassName("post-title")[0].text);
}

let removedItems = [];

function removeAndStore(element) {
	postsParent.removeChild(element);
	removedItems.push(element);
}

function addBack(element) {
	let temp = [];
	let inserted = false;

	const elementName = postTitle(element);

	console.debug(`Element Name to Add: ${elementName}`);
	console.debug(`Element Name Index: ${allItems.indexOf(elementName)}`);	
	const posts = postsParent.children;

	if(posts.length == 1 && allItems.indexOf(postTitle(posts[0])) > allItems.indexOf(elementName)) {
		postsParent.insertBefore(element, posts[0]);
		inserted = true;
	}

	for(let i = 0; i < posts.length - 1; i++) {

		if(allItems.indexOf(postTitle(posts[i])) < allItems.indexOf(elementName) && allItems.indexOf(postTitle(posts[i + 1])) > allItems.indexOf(elementName)) {
			postsParent.insertBefore(element, posts[i + 1]);
			inserted = true;
		}

	}

	if(!inserted) {
		postsParent.appendChild(element);
	}

	removedItems.splice(removedItems.indexOf(element), 1);
}
//#endregion


//#region Update Button OnClick
updateButton.addEventListener("click", () => {
	if (removedItems.length) {
		for (let i = 0; i < removedItems.length; i++) {
			if (passedFilterChecks(removedItems[i])) {
				addBack(removedItems[i--]);
			}
		}
	}

	for (let i = 0; i < postsParent.children.length; i++) {
		let element = postsParent.children[i];
		if (!passedFilterChecks(element)) {
			removeAndStore(element);
			i--;
		}
	}
});
//#endregion

//#region Filter Functions
function qualityFilter(element) {
	let toReturn = false;
	let anyChecked = false;
	[newFilter, excellentFilter, goodFilter, fairFilter, poorFilter].forEach((filter) => {
		const filterText = filter.value.toLowerCase();
		const elementText = element.attributes["data-condition"].value.toLowerCase();
		if (filter.checked && filterText == elementText) {
			toReturn = true; //I don't know why it has to 
		} else if (filter.checked) {
			anyChecked = true;
		}
	});

	return anyChecked ? toReturn : true;
}

function titleFilter(element) {
	const text = textFilter.value.toLowerCase();
	const toReturn = element.getElementsByClassName("post-title")[0].text.toLowerCase().indexOf(text) != -1;
	return text.length ? toReturn : true;
}

function priceFilter(element) {
	const elementPrice = parseInt(element.attributes["data-price"].value);
	const minPrice     = parseInt(minPriceFilter.value);
	const maxPrice     = parseInt(maxPriceFilter.value);

	if (!isNaN(minPrice) && !isNaN(maxPrice)) {
		return minPrice <= elementPrice && elementPrice <= maxPrice;
	} else if (!isNaN(minPrice)) {
		return minPrice <= elementPrice;
	} else if (!isNaN(maxPrice)) {
		return maxPrice >= elementPrice;
	} else {
		return true;
	}
}

function locationFilter(element) {
	const cityText = cityFilter.value.toLowerCase();
	const elementText = element.attributes["data-city"].value.toLowerCase();

	return cityText.length ? cityText == elementText : true;
}

function passedFilterChecks(element) {
	return titleFilter(element) &&
		qualityFilter(element) &&
		priceFilter(element) &&
		locationFilter(element);
}

//#endregion

//#endregion


//#region Add Post Logic


//#region Modal Global Vars

const modalBackdrop      = document.getElementById("modal-backdrop");
const sellSomethingModal = document.getElementById("sell-something-modal");

//#endregion


//#region Open Modal

const sellButton = document.getElementById("sell-something-button");

sellButton.onclick = () => {
	modalBackdrop.classList.remove("hidden");
	sellSomethingModal.classList.remove("hidden");
};

//#endregion

//#region Submit Post Logic

const postCondition     = document.getElementById("post-condition-fieldset");
const postName          = document.getElementById("post-text-input");
const postPhoto         = document.getElementById("post-photo-input");
const postPrice         = document.getElementById("post-price-input");
const postCity          = document.getElementById("post-city-input");

const cancelPost        = document.getElementById("modal-cancel");
const acceptPost        = document.getElementById("modal-accept");
const closeModal        = document.getElementById("modal-close");
const cityFilterOptions = document.getElementById("filter-city");

const addedCities = [];

for (var i in cityFilterOptions) {
	if (cityFilterOptions.hasOwnProperty(i) && cityFilterOptions[i].value.length) {
		if (!addedCities.some((entry) => {
			return entry.toLowerCase() == cityFilterOptions[i].value.toLowerCase();
		})) {
			addedCities.push(cityFilterOptions[i].value.toLowerCase());
		}
	}
}

acceptPost.onclick = () => {
	postsParent.innerHTML += `
    <div class="post" data-price="${postPrice.value}" data-city="${postCity.value}" data-condition="${postCondition.value}">
      <div class="post-contents">
        <div class="post-image-container">
          <img src="${postPhoto.value}" alt="${postName.value}">
        </div>
        <div class="post-info-container">
          <a href="#" class="post-title">${postName.value}</a> <span class="post-price">\$${postPrice.value}</span> <span class="post-city">(${postCity.value})</span>
        </div>
      </div>
	</div>`;
	
	allItems.push(postName.value);
	
	if (!addedCities.some((entry) => {
		return entry.toLowerCase() == postCity.value.toLowerCase();
	})) {
		cityFilterOptions.innerHTML += `<option>${postCity.value}</option>`;
		addedCities.push(postCity.value.toLowerCase());
	}

	clearAndClose();
};

cancelPost.onclick = clearAndClose;
closeModal.onclick = clearAndClose;

function clearAndClose() {
	postPrice.value     = "";
	postCity.value      = "";
	postCondition.value = "";
	postPhoto.value     = "";
	postName.value      = "";

	modalBackdrop.classList.add("hidden");
	sellSomethingModal.classList.add("hidden");
}



//#endregion




//#endregion
