package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"sort"
	"strings"
)

type Posts struct {
	Posts []Post `json:"posts"`
}
type Post struct {
	Author     string   `json:"author"`
	Authorid   int      `json:"authorid"`
	Id         int      `json:"id"`
	Likes      int      `json:"likes"`
	Popularity float32  `json:"popularity"`
	Reads      int      `json:"reads"`
	Tags       []string `json:"tags"`
}

type byId []Post

func (a byId) Len() int           { return len(a) }
func (a byId) Less(i, j int) bool { return a[i].Id < a[j].Id }
func (a byId) Swap(i, j int)      { a[i], a[j] = a[j], a[i] }

type byLikes []Post

func (a byLikes) Len() int           { return len(a) }
func (a byLikes) Less(i, j int) bool { return a[i].Likes < a[j].Likes }
func (a byLikes) Swap(i, j int)      { a[i], a[j] = a[j], a[i] }

type byReads []Post

func (a byReads) Len() int           { return len(a) }
func (a byReads) Less(i, j int) bool { return a[i].Likes < a[j].Likes }
func (a byReads) Swap(i, j int)      { a[i], a[j] = a[j], a[i] }

type byPopularity []Post

func (a byPopularity) Len() int           { return len(a) }
func (a byPopularity) Less(i, j int) bool { return a[i].Popularity < a[j].Popularity }
func (a byPopularity) Swap(i, j int)      { a[i], a[j] = a[j], a[i] }

func removeDupes(box Posts) Posts {
	keys := make(map[int]bool)
	noDupes := Posts{}
	for _, post := range box.Posts {
		if _, ok := keys[post.Id]; !ok {
			keys[post.Id] = true
			noDupes.Posts = append(noDupes.Posts, post)
		}
	}
	//fmt.Println(noDupes)
	return noDupes
}

func ping(w http.ResponseWriter, r *http.Request) {
	w.WriteHeader(http.StatusOK)
	resp := map[string]interface{}{
		"sucess": true,
	}
	jsonResp, _ := json.MarshalIndent(resp, "", "  ")
	w.Write(jsonResp)

}

func posts(w http.ResponseWriter, r *http.Request) {
	query := r.URL.Query().Get("tags")
	if len(query) > 0 {
		query2 := r.URL.Query().Get("sortby")
		query3 := r.URL.Query().Get("direction")
		fmt.Print(query, query2, query3)
		tags := strings.Split(query, ",")
		box := Posts{}
		var p Posts
		for _, tag := range tags {

			url := "https://api.hatchways.io/assessment/blog/posts?tag=" + tag

			fmt.Println(url)

			res, _ := http.Get(url)
			data, _ := ioutil.ReadAll(res.Body)
			//w.Write(data)
			res.Body.Close()
			json.Unmarshal(data, &p)
			box.Posts = append(box.Posts, p.Posts...)
		}
		if query2 == "id" || query2 == "likes" || query2 == "reads" || query2 == "popularity" || len(query2) == 0 {
			w.WriteHeader(http.StatusOK)
			switch query2 {
			case "id":
				if query3 == "desc" {
					sort.Sort(sort.Reverse(byId(box.Posts)))
				} else {
					sort.Sort(byId(box.Posts))
				}
			case "likes":
				if query3 == "desc" {
					sort.Sort(sort.Reverse(byLikes(box.Posts)))
				} else {
					sort.Sort(byLikes(box.Posts))
				}
			case "reads":
				if query3 == "desc" {
					sort.Sort(sort.Reverse(byReads(box.Posts)))
				} else {
					sort.Sort(byReads(box.Posts))
				}
			case "popularity":
				if query3 == "desc" {
					sort.Sort(sort.Reverse(byPopularity(box.Posts)))
				} else {
					sort.Sort(byPopularity(box.Posts))
				}
			default:
				sort.Sort(byId(box.Posts))
			}

			json.NewEncoder(w).Encode(removeDupes(box))
		}
		if query2 != "id" && query2 != "likes" && query2 != "reads" && query2 != "popularity" {
			w.WriteHeader(http.StatusBadRequest)
			resp := map[string]interface{}{
				"error": "sortby parameter is invalid",
			}
			jsonResp, _ := json.MarshalIndent(resp, "", "  ")
			w.Write(jsonResp)
		}

	} else {
		w.WriteHeader(http.StatusBadRequest)
		resp := map[string]interface{}{
			"error": "Tags parameter is required",
		}
		jsonResp, _ := json.MarshalIndent(resp, "", "  ")
		w.Write(jsonResp)
	}

}

func main() {
	http.HandleFunc("/api/ping", ping)
	http.HandleFunc("/api/posts", posts)
	log.Fatal(http.ListenAndServe(":8000", nil))
}
