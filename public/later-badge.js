// Adds a "later" badge to sidebar topics after the learner's current topic (PLAN.md Section 10.7).
(function () {
  var current;
  try {
    current = (JSON.parse(localStorage.getItem('cp:v1:settings') || '{}') || {}).currentTopic;
  } catch (e) {
    return;
  }
  if (!current) return;
  var links = document.querySelectorAll('a[data-topic][data-order]');
  var currentOrder = null;
  links.forEach(function (a) { if (a.getAttribute('data-topic') === current) currentOrder = Number(a.getAttribute('data-order')); });
  if (currentOrder === null) return;
  links.forEach(function (a) {
    if (Number(a.getAttribute('data-order')) > currentOrder && !a.querySelector('.later-badge')) {
      var s = document.createElement('span');
      s.className = 'later-badge';
      s.textContent = 'later';
      a.appendChild(s);
    }
  });
})();
