import Vue from 'vue'

import 'api/resource'
import App from 'pages/App.vue'
import { connect } from './util/ws'
import Vuetify from 'vuetify'
import 'vuetify/dist/vuetify.min.css'
import '@babel/polyfill'
import store from 'store/store'

if(profile) {
    connect()
}

Vue.use(Vuetify)
// Vue.use(VueResource)

new Vue({
    el: '#app',
    store,
    render: a => a(App)
})
